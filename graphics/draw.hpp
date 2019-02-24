/**
 * \file graphics/draw.hpp
 *
 * \author Simon Struthers <snstruthers@gmail.com>
 * \version pre_dev v0.1.0
 *
 * \section LICENSE
 * GenEx (short for General Executor) - window manager and runtime environment.
 * Copyright (C) 2019 | The GenEx Project
 *
 * This file is part of GenEx.
 *
 * GenEx is free software: you can redistribute it and/or modify it under the terms of the GNU
 * General Public License version 2 as published by the Free Software Foundation.
 *
 * GenEx is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at https://www.gnu.org/copyleft/gpl.html
 *
 * You should have received a copy of the GNU General Public License version 2 along with GenEx.
 * If not, see http://www.gnu.org/licenses.
 *
 * \section DESCRIPTION
 * The header file for drawing primitives & images to a target.
 *
 */

#ifndef GRAPHICS_DRAW_HPP
#define GRAPHICS_DRAW_HPP

#include "base.hpp"
#include "math.hpp"

namespace GenEx {
    namespace Graphics {
// --- RENDERING 2D IMAGES TO A TARGET ------------------------------------------------------------

        /** \brief Renders an SDL_Texture to a target with transformations if wanted.
         *
         * \param SDL_Texture *<u>img</u>: The image to render
         * \param SDL_Renderer *<u>target</u>: The target to render to
         * \param float <u>x</u>: The X-position of the image
         * \param float <u>y</u>: The Y-position of the image
         * \param SDL_Rect *<u>clipping_rect</u>: Pointer to a clipping box for the image;
         *        set to <i>nullptr</i> to render the whole image
         * \param float <u>offset_x</u>: How much to translate the image on the X-axis
         * \param float <u>offset_y</u>: How much to translate the image on the Y-axis
         * \param float <u><i>anchor_x</i></u>: The horizontal anchor for the image; set to 0.5
         *        by default; 0.0 for left, 1.0 for right
         * \param float <u><i>anchor_y</i></u>: The vertical anchor for the image; set to 0.5 by
         *        default; 0.0 for top, 1.0 for bottom
         * \param double <u><i>rotation</i></u>: How much to rotate the image in degrees; set to
         *        0 by default
         * \param float <u><i>scale_x</i></u>: How much to scale the image horizontally; set to
         *        1.0 by default; < 1 -> shrink; > 1 -> expand
         * \param float <u><i>scale_y</i></u>: How much to scale the image vertically; set to 1.0
         *        by default; < 1 -> shrink; > 1 -> expand
         * \param bool <u><i>flip_horizontal</i></u>: Whether or not to flip the image across the
         *        X-axis; set to FALSE by default
         * \param bool <u><i>flip_vertical</i></u>: Whether or not the flip the image across the
         *        Y-axis: set to FALSE by default
         * \return bool TRUE if rendering the image was successful
         *
         */
        bool RenderImg(SDL_Texture *img, SDL_Renderer *target, float x, float y,
                       SDL_Rect *clipping_rect, float offset_x, float offset_y,
                       float anchor_x = 0.5f, float anchor_y = 0.5f,
                       double rotation = 0.0, float scale_x = 1.f, float scale_y = 1.f,
                       bool flip_horizontal = false, bool flip_vertical = false);

        /** \brief Renders an SDL_Surface to a target with transformations if wanted.
         *
         * \param SDL_Surface *<u>surf</u>: The image to render
         * \param SDL_Renderer *<u>target</u>: The target to render to
         * \param float <u>x</u>: The X-position of the image
         * \param float <u>y</u>: The Y-position of the image
         * \param SDL_Rect *<u>clipping_rect</u>: Pointer to a clipping box for the image;
         *        set to <i>nullptr</i> to render the whole image
         * \param float <u>offset_x</u>: How much to translate the image on the X-axis
         * \param float <u>offset_y</u>: How much to translate the image on the Y-axis
         * \param float <u><i>anchor_x</i></u>: The horizontal anchor for the image; set to 0.5
         *        by default; 0.0 for left, 1.0 for right
         * \param float <u><i>anchor_y</i></u>: The vertical anchor for the image; set to 0.5 by
         *        default; 0.0 for top, 1.0 for bottom
         * \param double <u><i>rotation</i></u>: How much to rotate the image in degrees; set to
         *        0 by default
         * \param float <u><i>scale_x</i></u>: How much to scale the image horizontally; set to
         *        1.0 by default; < 1 -> shrink; > 1 -> expand
         * \param float <u><i>scale_y</i></u>: How much to scale the image vertically; set to 1.0
         *        by default; < 1 -> shrink; > 1 -> expand
         * \param bool <u><i>flip_horizontal</i></u>: Whether or not to flip the image across the
         *        X-axis; set to FALSE by default
         * \param bool <u><i>flip_vertical</i></u>: Whether or not the flip the image across the
         *        Y-axis: set to FALSE by default
         * \return bool TRUE if rendering the image was successful
         *
         */
        bool RenderImg(SDL_Surface *surf, SDL_Renderer *target, float x, float y,
                       SDL_Rect *clipping_rect, float offset_x, float offset_y,
                       float anchor_x = 0.5, float anchor_y = 0.5,
                       double rotation = 0.0, float scale_x = 1.0f, float scale_y = 1.0f,
                       bool flip_horizontal = false, bool flip_vertical = false);

// --- PRIMITIVES ---------------------------------------------------------------------------------

        /** \brief Renders an antialiased line to a given target.
         *
         * \param SDL_Renderer *<u>target</u>: The target to render to
         * \param SDL_Color <u>color</u>: The color to draw the line
         * \param int <u>x0</u>: The X-coordinate of the first point
         * \param int <u>y0</u>: The Y-coordinate of the first point
         * \param int <u>x1</u>: The X-coordinate of the second point
         * \param int <u>y1</u>: The Y-coordinate of the second point
         * \param float <u>wd</u>: The width of the line
         *
         */
        void RenderLine(SDL_Renderer *target, SDL_Color color,
                        int x0, int y0, int x1, int y1, float wd);

        /** \brief Renders multiple lines to a given target.
         *
         * \param SDL_Renderer *<u>target</u>: The target to render to
         * \param SDL_Color <u>color</u>: The color to draw the lines
         * \param std::vector<Math::Vector<2,T>> &<u>pts</u>: Reference to a vector containing
         *        2D points to connect together as lines
         * \param float <u>wd</u>: The width of the lines
         *
         */
        template <typename T>
        void RenderLines(SDL_Renderer *target, SDL_Color color,
                         std::vector< Math::Vector<2,T> > &pts, float wd);

        /** \brief Renders a Bezier curve onto a given target.
         *
         * \param Math::Bezier <u>bezier</u>: The Bezier curve to render
         * \param SDL_Renderer *<u>target</u>: The target to render onto
         * \param SDL_Color <u>color</u>: The color to draw the curve
         * \param float <u><i>thickness</i></u>: The thickness of the curve to be drawn; defaults
         *        to 1.0f
         * \param unsigned int <u><i>samples</i></u>: How many samples from which to interpolate
         *        this curve; defaults to <i>Math::DEFAULT_SAMPLES</i>
         *
         */
        template <typename T>
        void RenderBezier(Math::Bezier<T> bezier, SDL_Renderer *target, SDL_Color color,
                          float thickness = 1.0f, unsigned int samples = Math::DEFAULT_SAMPLES);

        /** \brief Renders a path of Bezier curves to a given target.
         *
         * \param Math::Path <u>path</u>: The path to render
         * \param SDL_Renderer *<u>target</u>: The target to render onto
         * \param SDL_Color <u>color</u>: The color to draw the path
         * \param float <u><i>thickness</i></u>: The thickness of the curve to be drawn; defaults
         *        to 1.0f
         *
         */
        template <typename T>
        void RenderPath(Math::Path<T> &path, SDL_Renderer *target, SDL_Color color,
                        float thickness = 1.0f);
    };
};

#endif // GRAPHICS_DRAW_HPP
