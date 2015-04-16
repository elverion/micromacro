#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "15";
	static const char MONTH[] = "04";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.04";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 92;
	static const long BUILD  = 43;
	static const long REVISION  = 1002;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 1187;
	#define RC_FILEVERSION 1,92,43,1002
	#define RC_FILEVERSION_STRING "1, 92, 43, 1002\0"
	static const char FULLVERSION_STRING [] = "1.92.43.1002";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 116;
	

}
#endif //VERSION_H
