/**
 * @file godot_math.cpp
 * 
 * This file contains modified code from the Godot Project.
 * 
 * Original Code: Copyright (c) 2014-present Godot Engine contributors (see Godot Engine's AUTHORS.md).
 * Original Code: Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.  
 * Modified Code: Copyright (c) 2025 Rubyboat (owner of https://github.com/Rubyboat1207)
 * 
 * The original code was licensed under the MIT license. The full license text follows.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the       
 * "Software"), to deal in the Software without restriction, including   
 * without limitation the rights to use, copy, modify, merge, publish,   
 * distribute, sublicense, and/or sell copies of the Software, and to    
 * permit persons to whom the Software is furnished to do so, subject to 
 * the following conditions:                                             
 *                                                                       
 * The above copyright notice and this permission notice shall be        
 * included in all copies or substantial portions of the Software.       
 *                                                                       
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                
 * 
 */

#include "math.hpp"


// This is split into a separate file because these functions are under a different license
// because they are taken from the godot engine.

void Vector2f::moveTowardsWithState(Vector2f to, float delta)
{
	Vector2f vd = to - this;
	float len = vd.length();
    if(len <= delta || len < 0.5f ) {
        x = to.x;
        y = to.y;
        return;
    }
    Vector2f addened = vd / len * delta;
    x += addened.x;
    y += addened.y;
}

Vector2f Vector2f::vectorMovedTowards(Vector2f to, float delta)
{
    Vector2f v = *this;
	Vector2f vd = to - v;
	float len = vd.length();
	return len <= delta || len < 0.5f ? to : v + vd / len * delta;
}