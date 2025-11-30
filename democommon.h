/*
 *
 */

#ifndef DEMOCOMMON_H_552F7375_1BA4_4f12_91F4_51950EF31347
#define DEMOCOMMON_H_552F7375_1BA4_4f12_91F4_51950EF31347

#include "picosystem_hardware.h"

#define SCREEN_WIDTH	PICOSYSTEM_SCREEN_WIDTH
#define SCREEN_HEIGHT	PICOSYSTEM_SCREEN_HEIGHT

#include "vector_math.h"
#include "fixed_class.h"

using namespace vmath;
using namespace fixedpoint;

typedef fixed_point<16> fixed16_t;

typedef vec2<fixed16_t> vec2x;
typedef vec3<fixed16_t> vec3x;
typedef vec4<fixed16_t> vec4x;
typedef mat4<fixed16_t> mat4x;

#define X(a) fixed16_t(a)

#include <algorithm>

inline void fade_effect(color_t *s, bool ltr, float t)
{
	// Fade effect disabled for PicoSystem
	(void)s;
	(void)ltr;
	(void)t;
}

#endif
