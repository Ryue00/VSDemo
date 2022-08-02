#pragma once
/**
 * Copyright (c) 2021, INTRE All rights reserved.
 *
 * @Description: RGB --> xyz --> XY
 * @author: RYue00
 * @date: 2021-03-08
 * @version: v1.1
 */

#include "TypeDef.h"
#define MAX3(X,Y,Z)     ((Y) >= (Z) ? ((X) >= (Y) ? (X) : (Y)) : ((X) >= (Z) ? (X) : (Z)))

/**
 * ٤��У׼
 */
uint16 GammaCorrection(int16 numberRGB);

/**
 * RGB ת���� XY
 */

/**
 * ��ȡRGB
 */
void XY2RGB(uint16 currentX, uint16 currentY, uint16* r, uint16* g, uint16* b);

/**
 * ���� RGBתxyY�ľ���
 */
bool CreateCrx(double Crx[3][3]);

/**
 * ���� xyYתRGB�ľ���
 */
bool CreateCxr(float Cxr[3][3]);

/**
 * RGB ת���� XY
 */
bool RGB2XY(const uint16 red, const uint16 green, const uint16 blue, uint16& currentX, uint16& currentY);

/**
 * �ж�ֵ�Ƿ���� 0
 */
bool IsEqualToZero(const double value)
{
	const double EPSINON = 0.000000000001;

	if ((value >= -EPSINON) && (value <= EPSINON))
	{
		return true;
	}
	return false;
}

/**
 * XYZ ת���� RGB
 */
bool XYZ2RGB(
		    float  afMatrix[3][3],
		    float  fX,
		    float  fY,
		    float  fZ,
		    float* pfRed,
		    float* pfGreen,
		    float* pfBlue);