#pragma once

//square which the x axis goes through
//same for the others
const float squarex[4][3] = {
	{0.0f, 0.0f, 1.0f}, //left down
	{0.0f, 0.0f, 0.0f}, //right down
	{0.0, 1.0f, 1.0f}, 	//left up
	{0.0f, 1.0f, 0.0f}, //right up
};

const float squarey[4][3] = {
	{0.0f, 0.0f, 1.0f},
	{1.0, 0.0f, 1.0f},
	{0.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
};

const float squarez[4][3] = {
	{0.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{1.0, 1.0f, 0.0f},
};

//default tex coords
const float defaulttexcoords[4][2] = {
	{0.0f, 0.0f}, //left down
	{1.0f, 0.0f}, //right down
	{0.0f, 1.0f}, //left up
	{1.0f, 1.0f}, //right up
};

//normal vector x, y, z
const float normals[3][3] = {
	{1.0f, 0.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 0.0f, 1.0f},
};

//normal vector -x, -y, -z
const float normalsreverse[3][3] = {
	{-1.0f, 0.0f, 0.0f},
	{0.0f, -1.0f, 0.0f},
	{0.0f, 0.0f, -1.0f},
};
