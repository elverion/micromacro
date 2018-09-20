/******************************************************************************
	Project: 	MicroMacro
	Author: 	SolarStrike Software
	URL:		www.solarstrike.net
	License:	Modified BSD (see license.txt)
******************************************************************************/

//	Generated:	1537472800

#ifndef ENCSTRING_H
#define ENCSTRING_H

	#include <stdlib.h>

	namespace EncString
	{
		size_t reveal(char *, size_t, const int *);
		const unsigned long enckey = 622089297;

		const int logVersionFmt[] = {
			0x2514541c, 0x25145438, 0x25145432, 0x25145423, 0x2514543e, 0x2514541c, 0x25145430, 0x25145432,
			0x25145423, 0x2514543e, 0x25145471, 0x25145427, 0x25145434, 0x25145423, 0x25145422, 0x25145438,
			0x2514543e, 0x2514543f, 0x25145471, 0x25145474, 0x25145422, 0x25145471, 0x25145479, 0x25145474,
			0x25145422, 0x25145478, 0x25145471, 0x25145474, 0x25145422, 0x2514545b, 0};
		const int basicTitle[] = {
			0x2514541c, 0x25145438, 0x25145432, 0x25145423, 0x2514543e, 0x2514541c, 0x25145430, 0x25145432,
			0x25145423, 0x2514543e, 0x25145471, 0x25145427, 0x25145474, 0x2514543d, 0x25145435, 0x2514547f,
			0x25145474, 0x25145461, 0x25145463, 0x2514543d, 0x25145435, 0x2514547f, 0x25145474, 0x2514543d,
			0x25145435, 0};
		const int website[] = {
			0x25145402, 0x2514543e, 0x2514543d, 0x25145430, 0x25145423, 0x25145402, 0x25145425, 0x25145423,
			0x25145438, 0x2514543a, 0x25145434, 0x25145471, 0x25145402, 0x2514543e, 0x25145437, 0x25145425,
			0x25145426, 0x25145430, 0x25145423, 0x25145434, 0x25145458, 0x25145439, 0x25145425, 0x25145425,
			0x25145421, 0x2514546b, 0x2514547e, 0x2514547e, 0x25145426, 0x25145426, 0x25145426, 0x2514547f,
			0x25145422, 0x2514543e, 0x2514543d, 0x25145430, 0x25145423, 0x25145422, 0x25145425, 0x25145423,
			0x25145438, 0x2514543a, 0x25145434, 0x2514547f, 0x2514543f, 0x25145434, 0x25145425, 0};
		const int taskIconTitle[] = {
			0x2514541c, 0x25145438, 0x25145432, 0x25145423, 0x2514543e, 0x2514541c, 0x25145430, 0x25145432,
			0x25145423, 0x2514543e, 0};
	}
#endif
