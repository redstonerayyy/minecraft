#ifndef PRIMITIVEDATA_H
#define PRIMITIVEDATA_H

//vertices orientated upwards
const float triangle[3][3] = {
	{0.0f, 0.0f, 0.0f},
	{0.0, 1.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
};

const float squarex[4][3] = {
	{0.0f, 0.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0, 1.0f, -1.0f},
	{0.0f, 0.0f, -1.0f},
};

const float squarey[4][3] = {
	{0.0f, 0.0f, 0.0f},
	{-1.0f, 0.0f, 0.0f},
	{-1.0, 0.0f, -1.0f},
	{0.0f, 0.0f, -1.0f},
};

const float squarez[4][3] = {
	{0.0f, 0.0f, 0.0f},
	{-1.0f, 0.0f, 0.0f},
	{-1.0, 1.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
};

#endif