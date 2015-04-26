/******************************************************************************
	Project: 	MicroMacro
	Author: 	SolarStrike Software
	URL:		www.solarstrike.net
	License:	Modified BSD (see license.txt)
******************************************************************************/

//	Generated:	1430068020

#ifndef ENCSTRING_H
#define ENCSTRING_H

	#include <stdlib.h>

	namespace EncString
	{
		size_t reveal(char *, size_t, const int *);
		const unsigned long enckey = 90151678;

		const int basicTitle[] = {
			0x55f9ab3, 0x55f9a97, 0x55f9a9d, 0x55f9a8c, 0x55f9a91, 0x55f9ab3, 0x55f9a9f, 0x55f9a9d,
			0x55f9a8c, 0x55f9a91, 0x55f9ade, 0x55f9a88, 0x55f9adb, 0x55f9a92, 0x55f9a9a, 0x55f9ad0,
			0x55f9adb, 0x55f9ace, 0x55f9acc, 0x55f9a92, 0x55f9a9a, 0x55f9ad0, 0x55f9adb, 0x55f9a92,
			0x55f9a9a, 0};
		const int website[] = {
			0x55f9aad, 0x55f9a91, 0x55f9a92, 0x55f9a9f, 0x55f9a8c, 0x55f9aad, 0x55f9a8a, 0x55f9a8c,
			0x55f9a97, 0x55f9a95, 0x55f9a9b, 0x55f9ade, 0x55f9aad, 0x55f9a91, 0x55f9a98, 0x55f9a8a,
			0x55f9a89, 0x55f9a9f, 0x55f9a8c, 0x55f9a9b, 0x55f9af7, 0x55f9a96, 0x55f9a8a, 0x55f9a8a,
			0x55f9a8e, 0x55f9ac4, 0x55f9ad1, 0x55f9ad1, 0x55f9a89, 0x55f9a89, 0x55f9a89, 0x55f9ad0,
			0x55f9a8d, 0x55f9a91, 0x55f9a92, 0x55f9a9f, 0x55f9a8c, 0x55f9a8d, 0x55f9a8a, 0x55f9a8c,
			0x55f9a97, 0x55f9a95, 0x55f9a9b, 0x55f9ad0, 0x55f9a90, 0x55f9a9b, 0x55f9a8a, 0};
		const int logVersionFmt[] = {
			0x55f9ab3, 0x55f9a97, 0x55f9a9d, 0x55f9a8c, 0x55f9a91, 0x55f9ab3, 0x55f9a9f, 0x55f9a9d,
			0x55f9a8c, 0x55f9a91, 0x55f9ade, 0x55f9a88, 0x55f9a9b, 0x55f9a8c, 0x55f9a8d, 0x55f9a97,
			0x55f9a91, 0x55f9a90, 0x55f9ade, 0x55f9adb, 0x55f9a8d, 0x55f9ade, 0x55f9ad6, 0x55f9adb,
			0x55f9a8d, 0x55f9ad7, 0x55f9ade, 0x55f9adb, 0x55f9a8d, 0x55f9af4, 0};
	}
#endif
