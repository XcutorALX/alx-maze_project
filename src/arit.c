#include "maze.h"

/**
 * custom_round - this function helps with rounding
 *
 * @value: the value to be rounded
 *
 * Return: the return value
 */

int custom_round(float value) {
    float floored = floor(value);   // Get the floored value
    float fractional = value - floored; // Calculate the fractional part

    // If the fractional part is greater than 0.9, round up
    if (fractional > 0.97) {
        return ceil(value); // Round up
    } else {
        return (int) floored; // Otherwise, return the floored value
    }
}
