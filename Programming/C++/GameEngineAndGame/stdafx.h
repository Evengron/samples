// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <memory>
#include <string>
#include <list>
#include <algorithm>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

// since we only use sfml and no other libraries, we 
// can add a using namespace here. Be careful though
// when doing that!
using namespace sf;

// own headers that are stable, do rarely change and do not contain 
// include files of parts of the program that changes frequently
#include "Debug.h"
#include "DebugDraw.h"
#include "Trigonometry.h"
#include "VectorAlgebra2D.h"
#include "VectorAlgebra3D.h"