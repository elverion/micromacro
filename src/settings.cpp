/******************************************************************************
	Project: 	MicroMacro
	Author: 	SolarStrike Software
	URL:		www.solarstrike.net
	License:	Modified BSD (see license.txt)
******************************************************************************/

#include "settings.h"

/* Setting value stuff */
CSettingValue::CSettingValue()
{
	iValue = 0;
	type = ST_NIL;
}

CSettingValue::CSettingValue(double d)
{
	setFloat(d);
}

CSettingValue::CSettingValue(int d)
{
	setInt(d);
}

CSettingValue::CSettingValue(std::string d)
{
	setString(d);
}

SettingType CSettingValue::getType()
{
	return type;
}

double CSettingValue::getFloat()
{
	return fValue;
}

void CSettingValue::setFloat(double d)
{
	fValue = d;
	type = ST_FLOAT;
}

int CSettingValue::getInt()
{
	return iValue;
}

void CSettingValue::setInt(int d)
{
	iValue = d;
	type = ST_INT;
}

std::string CSettingValue::getString()
{
	return szValue;
}

void CSettingValue::setString(std::string d)
{
	szValue = d;
	type = ST_INT;
}

void CSettingValue::setNil()
{
	szValue = ""; // Might as well get rid of unnecessary memory
	type = ST_NIL;
}


/* Our actual setting container */
CSettings::CSettings()
{
}

CSettings::~CSettings()
{
}

void CSettings::setFloat(std::string key, double nv)
{
	settingsmap[key].setFloat(nv);
}

void CSettings::setInt(std::string key, int nv)
{
	settingsmap[key].setInt(nv);
}

void CSettings::setString(std::string key, std::string nv)
{
	settingsmap[key].setString(nv);
}

double CSettings::getFloat(std::string key, double defaultValue)
{
	t_settingsmap::iterator foundpos = settingsmap.find(key);
	if( foundpos != settingsmap.end() )
		return foundpos->second.getFloat();

	return defaultValue;
}

int CSettings::getInt(std::string key, int defaultValue)
{
	t_settingsmap::iterator foundpos = settingsmap.find(key);
	if( foundpos != settingsmap.end() )
		return foundpos->second.getInt();

	return defaultValue;
}

std::string CSettings::getString(std::string key, std::string defaultValue)
{
	t_settingsmap::iterator foundpos = settingsmap.find(key);
	if( foundpos != settingsmap.end() )
		return foundpos->second.getString();

	return defaultValue;
}

void CSettings::clear(std::string key)
{
	t_settingsmap::iterator foundpos = settingsmap.find(key);
	if( foundpos != settingsmap.end() )
		settingsmap.erase(foundpos);
}

void CSettings::clearAll()
{
	settingsmap.clear();
}
