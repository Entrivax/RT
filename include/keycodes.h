/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 14:57:20 by lpilotto          #+#    #+#             */
/*   Updated: 2016/06/13 15:35:37 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
# define KEYCODES_H

# ifdef MAC
/*
** KEYBOARD LINE 1
*/
#  define K_ESC 53
#  define K_F1 122
#  define K_F2 120
#  define K_F3 99
#  define K_F4 118
#  define K_F5 96
#  define K_F6 97
#  define K_F7 98
#  define K_F8 100
#  define K_F9 101
#  define K_F10 109
#  define K_F11 103
#  define K_F12 111
#  define K_PRINT 105
#  define K_SCROLLLOCK 107
#  define K_PAUSE 113
/*
** /!\ WARNING THOSE KEY DOESN'T EXIST ON CLASSIC KEYBOARDS /!\
*/
#  define K_EJECT 53
#  define K_F16 106
#  define K_F17 64
#  define K_F18 79
#  define K_F19 80
/*
** /!\ END OF WARNING /!\
*/

/*
** KEYBOARD LINE 2
*/
#  define K_BACKQUOTE 50
#  define K_1 18
#  define K_2 19
#  define K_3 20
#  define K_4 21
#  define K_5 23
#  define K_6 22
#  define K_7 26
#  define K_8 28
#  define K_9 25
#  define K_0 29
#  define K_MINUS 27
#  define K_EQUAL 24
#  define K_BACK 51
#  define K_NUMLOCK 279
#  define K_HOME 115
#  define K_PAGEUP 116
/*
** /!\ WARNING THIS KEY DOESN'T EXIST ON CLASSIC KEYBOARDS /!\
*/
#  define K_PEQUAL 71
/*
** /!\ END OF WARNING /!\
*/
#  define K_PSLASH 81
#  define K_PSTAR 67

/*
** KEYBOARD LINE 3
*/
#  define K_TAB 48
#  define K_Q 12
#  define K_W 13
#  define K_E 14
#  define K_R 15
#  define K_T 17
#  define K_Y 16
#  define K_U 32
#  define K_I 34
#  define K_O 31
#  define K_P 35
#  define K_BRACKET_O 33
#  define K_BRACKET_C 30
#  define K_BACKSLASH 42
#  define K_DELETE 117
#  define K_END 119
#  define K_PAGEDOWN 121
#  define K_P7 89
#  define K_P8 91
#  define K_P9 92
#  define K_PMINUS 78

/*
** KEYBOARD LINE 4
*/
#  define K_CAPSLOCK 272
#  define K_A 0
#  define K_S 1
#  define K_D 2
#  define K_F 3
#  define K_G 5
#  define K_H 4
#  define K_J 38
#  define K_K 40
#  define K_L 37
#  define K_SEMICOLON 41
#  define K_QUOTE 39
#  define K_RETURN 36
#  define K_P4 86
#  define K_P5 87
#  define K_P6 88
#  define K_PPLUS 69

/*
** KEYBOARD LINE 5
*/
#  define K_LSHIFT 257
#  define K_Z 6
#  define K_X 7
#  define K_C 8
#  define K_V 9
#  define K_B 11
#  define K_N 45
#  define K_M 46
#  define K_COMMA 43
#  define K_DOT 47
#  define K_SLASH 44
#  define K_RSHIFT 258
#  define K_UP 126
#  define K_P1 83
#  define K_P2 84
#  define K_P3 85
#  define K_PRETURN 76

/*
** KEYBOARD LINE 6
*/
#  define K_CTRL 256
#  define K_LWIN 261
#  define K_LALT 259
#  define K_SPACE 49
#  define K_RALT 260
#  define K_RWIN 262
#  define K_RCTRL 269
#  define K_LEFT 123
#  define K_DOWN 125
#  define K_RIGHT 124
#  define K_P0 82
#  define K_PDELETE 65

# elif LINUX

# endif

#endif
