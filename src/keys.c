#include "struct.h"

/**
 * handle_key_event - handles the key event
 *
 * @code: the keycode
 * @status: current status of the key
 * @keys: a Gamepad struct for easier usage
 *
 * Return: None
 */
void handle_key_event(int code, Gamepad *keys, int status)
{
	switch (code)
	{
		case KEY_W:
			keys->forward = status;
			break;
		case KEY_A:
			keys->left = status;
			break;
		case KEY_S:
			keys->backward = status;
			break;
		case KEY_D:
			keys->right = status;
			break;
		case KEY_LEFT:
			keys->rot_left = status;
			break;
		case KEY_RIGHT:
			keys->rot_right = status;
			break;
		default:
			break;
	}
}
