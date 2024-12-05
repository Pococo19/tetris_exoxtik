#include "../include/colors.h"

const Color dark_grey = {26, 31, 30, 255};
const Color green = {47, 230, 23, 255};
const Color red = {232, 18, 18, 255};
const Color orange = {226, 116, 17, 255};
const Color yellow = {253, 249, 0, 255};
const Color cyan = {21, 204, 209, 255};
const Color purple = {166, 0, 247, 255};
const Color blue = {13, 64, 216, 255};

std::vector<Color> get_cell_color()
{
    return {dark_grey, green, red, blue, cyan, purple, orange, yellow};
}
