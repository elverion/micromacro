require 'console/output'
require 'unittest/assert'

UnitTest = class.new()
function UnitTest:constructor(args)
    self.root = filesystem.getCWD()
    self.testDirectory = "tests";
    self.output = ConsoleOutput()

    self.showAssertionTraceback = false
    self.assertCount = 0

    self.filterFiles = nil

    self.shouldRun = true
    self:handleArgs(args)
end

function UnitTest:showHelp()
    local helps = {
        ['--help'] = "You're looking at it",
        ['--verbose'] = "Provide more detailed output when available.",
        ['--filter-files={filters}'] = "Filter files in the `tests` directory. Should be comma-separted Lua patterns." ..
            sprintf("\n%33s%s", "",
                "Ex: " .. self.output:sstyle('success', "test my-project --filter-files=test_.*  ") ..
                    self.output:sstyle('petty', "Only use files beginning with `test_`"))
    }
    self.output:writeln('Example:\t' .. self.output:sstyle('success', 'test my-project'))
    self.output:writeln('\nOptions:')
    for i, v in pairs(helps) do
        local padding = string.rep(' ', 30 - string.len(i))
        self.output:writeln(sprintf("   %s%s%s", self.output:sstyle('success', i), padding, v))
    end

    self.output:writeln('')
end

function UnitTest:handleArgs(args)
    local optHandlers = {
        ['--filter-files'] = function(filters)
            self.filterFiles = string.explode(filters, ',')
        end,
        ['--verbose'] = function()
            self.showAssertionTraceback = true
        end,
        ['--help'] = function()
            self:showHelp()
            return false
        end
    }

    for i, v in pairs(args) do
        local splitPos = string.find(v, '=')
        local opt = v
        local optValue = nil
        if splitPos then
            opt = string.sub(v, 1, splitPos - 1)
            optValue = string.sub(v, splitPos + 1)
        end

        if optHandlers[opt] ~= nil then
            local shouldContinue = optHandlers[opt](optValue)
            if shouldContinue == false then
                self.shouldRun = false
            end
        else
            error(sprintf("Unknown option `%s`", opt), 0)
        end
    end
end

function UnitTest:getAssertCount()
    return self.assertCount
end

function UnitTest:incrementAssertCount()
    self.assertCount = self.assertCount + 1
end

function UnitTest:run()
    if (not self.shouldRun) then
        return 0
    end
    local scanPath<const> = self.root .. '/' .. self.testDirectory .. '/'

    local files = self:findTestFiles(scanPath)

    self.output:info("Running tests")
    local succeeded = {}
    local failed = {}
    local successCount = 0
    local failCount = 0
    local originalAssert = assert

    self.successCount = 0
    assert = function(...)
        self:incrementAssertCount()

        local success, v, msg = pcall(originalAssert, ...)
        if success then
            return v, msg
        else
            error(v, 2)
        end
    end

    for i, v in pairs(files) do
        local s, f, memoryUsed = self:runTestsInFile(scanPath, v)
        succeeded = table.merge(succeeded, s)
        failed = table.merge(failed, f)

        successCount = successCount + #s
        failCount = failCount + #f
    end
    assert = originalAssert

    self:printFailures(failed)

    self.output:writeln(sprintf("\nTests: %d, Assertions: %d, Passed: %d, Failed: %d", successCount + failCount,
        self:getAssertCount(), successCount, failCount))

    -- Ensure that the script now terminates gracefully, and does not end up trying to run
    -- real initialization and main loops
    macro.init = function()
    end
    macro.main = function()
        return false
    end

    if failCount > 0 then
        return -1
    else
        return 0
    end
end

function UnitTest:findTestFiles(path)
    local results<const> = filesystem.getDirectory(path)
    local files = {}
    for i, v in pairs(results) do
        local pathToNew<const> = path .. v

        if (filesystem.isDirectory(pathToNew)) then
            -- Recurse over subdirectories, append to our list
            for j, k in pairs(self:findTestFiles(pathToNew .. "/")) do
                table.insert(files, v .. "/" .. k)
            end
        else
            if self.filterFiles == nil then
                if (string.sub(v, -4) == ".lua") then
                    table.insert(files, v)
                end
            else
                for i, pattern in pairs(self.filterFiles) do
                    if string.match(v, pattern) then
                        table.insert(files, v)
                    end
                end
            end
        end
    end

    return files
end

function UnitTest:runTestsInFile(root, relativeFilePath)
    local path<const> = root .. relativeFilePath

    -- Create a new environment to run in, then run the chunk
    local env = setmetatable({}, {
        __index = _G
    })
    local chunk = loadfile(path, nil, env)
    chunk()

    -- Locate test functions within the environment and run try them
    local succeeded = {}
    local failed = {}
    local testCount = 0
    for functionName, ptrToTestFunction in pairs(env) do
        if (type(ptrToTestFunction) == "function" and string.sub(functionName, 1, 5) == "test_") then
            local traceback = nil
            local errMsg = ''
            local errorHandler = function(err)
                errMsg = err

                -- If the error message is the standard assert fail message, it must be an assertion fail
                local isAssertionFail = string.sub(err, -(string.len(Assert.getFailMessage()))) ==
                                            Assert.getFailMessage()

                if (not isAssertionFail) then
                    traceback = debug.traceback(nil, 2)
                elseif self.showAssertionTraceback then
                    -- Have to move further up the stack to account for our wrapped assert call
                    traceback = debug.traceback(nil, 4)
                end
            end

            local asserter = Assert(self)
            local origAssertCount = self:getAssertCount()
            local testname<const> = sprintf("%s::%s", self.testDirectory .. '/' .. relativeFilePath, functionName)
            local origStdout = io.stdout
            local startTime = time.getNow()
            local success = xpcall(ptrToTestFunction, errorHandler, asserter)
            local endTime = time.getNow()
            local passOrFail = "";
            local newAssertCount = self:getAssertCount()

            testCount = testCount + 1

            local description = testname
            local descriptionStyle = 'default'
            if newAssertCount == origAssertCount then
                passOrFail = self.output:sstyle('comment', 'WARN')
                description = description .. ' has no assertions'
                descriptionStyle = 'comment'
            elseif (success) then
                table.insert(succeeded, testname)
                passOrFail = self.output:sstyle('success', 'PASS')
            else
                table.insert(failed, {
                    name = testname,
                    errors = errMsg,
                    trace = traceback
                })

                passOrFail = self.output:sstyle('fail', 'FAIL')
            end

            local padding = self.output:sstyle('petty', string.rep('.', 60 - string.len(description)))
            local runtime = sprintf("%0.2fms", time.diff(endTime, startTime) * 1000)
            self.output:writeln(sprintf(" [%s]  %s %s %s", passOrFail,
                self.output:sstyle(descriptionStyle, description), padding, runtime))
        end
    end

    if (testCount == 0) then
        self.output:writeln(sprintf(" [%s]  %s", self.output:sstyle('comment', 'WARN'),
            self.output:sstyle('comment', 'No tests in ' .. relativeFilePath)))
    end

    -- Cleanup our temporary environment
    local memoryBeforeCleanup<const> = collectgarbage('count')
    env = nil
    collectgarbage("collect")
    local memoryFreed = memoryBeforeCleanup - collectgarbage('count')

    return succeeded, failed, memoryFreed
end

function UnitTest:printFailures(failed)
    for i, details in pairs(failed) do
        self.output:writeln("\n")
        self.output:error("Test: " .. details['name'])
        self.output:default(details['errors'])

        if (details['trace'] ~= nil) then
            self.output:petty(details['trace'])
        end
    end
end
