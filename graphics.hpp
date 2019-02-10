#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

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
                       bool flip_horizontal = false, bool flip_vertical = false) {
            if (img == nullptr || target == nullptr) return false;

            int tw, th; // get width & height
            SDL_QueryTexture(img, nullptr, nullptr, &tw, &th);

            float w, h;
            w = scale_x * tw;
            h = scale_y * th;

            SDL_Rect dstrect;
			dstrect.x = x - (w  * anchor_x);
			dstrect.x += offset_x;
			dstrect.y = y - (h * anchor_y);
			dstrect.y += offset_y;
			dstrect.w = (int)w;
			dstrect.h = (int)h;

			//SDL_Point center = {center_x, center_y};

			SDL_RendererFlip flip = SDL_FLIP_NONE;
			if (flip_horizontal && flip_vertical) {
                flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
			} else if (flip_horizontal) {
                flip = SDL_FLIP_HORIZONTAL;
			} else if (flip_vertical) {
                flip = SDL_FLIP_VERTICAL;
			}

            return SDL_RenderCopyEx(target, img, clipping_rect, &dstrect,
                                    rotation, nullptr, flip) == 0;
        }

        bool RenderImg(SDL_Surface *surf, SDL_Renderer *target, float x, float y,
                       SDL_Rect *clipping_rect, float offset_x, float offset_y,
                       float anchor_x = 0.5, float anchor_y = 0.5,
                       double rotation = 0.0, float scale_x = 1.0f, float scale_y = 1.0f,
                       bool flip_horizontal = false, bool flip_vertical = false) {
            SDL_Texture *tex = SDL_CreateTextureFromSurface(target, surf);
            if (tex == nullptr) {
                return false;
            }
            bool ret_val = RenderImg(tex, target, x, y, clipping_rect, offset_x, offset_y,
                                     anchor_x, anchor_y, rotation, scale_x, scale_y,
                                     flip_horizontal, flip_vertical);
            SDL_DestroyTexture(tex);
            return ret_val;
        }

// --- PRIMITIVES ---------------------------------------------------------------------------------

        void RenderCircle(SDL_Renderer *target, SDL_Color color,
                          float _x, float _y, int radius) {
            Uint8 r,g,b,a;
            SDL_GetRenderDrawColor(target, &r, &g, &b, &a);
            SDL_SetRenderDrawColor(target, color.r, color.g, color.b, color.a);

            float x = radius - 1;
            float y = 0;
            float tx = 1;
            float ty = 1;
            float err = tx - (radius << 1);
            while (x >= y) {
                SDL_RenderDrawPoint(target, _x + x, _y - y);
                SDL_RenderDrawPoint(target, _x + x, _y + y);
                SDL_RenderDrawPoint(target, _x - x, _y - y);
                SDL_RenderDrawPoint(target, _x - x, _y + y);
                SDL_RenderDrawPoint(target, _x + y, _y - x);
                SDL_RenderDrawPoint(target, _x + y, _y + x);
                SDL_RenderDrawPoint(target, _x - y, _y - x);
                SDL_RenderDrawPoint(target, _x - y, _y + x);

                if (err <= 0) {
                    y++;
                    err += ty;
                    ty += 2;
                }
                if (err > 0) {
                    x--;
                    tx += 2;
                    err += tx - (radius << 1);
                }
            }

            SDL_SetRenderDrawColor(target, r, g, b, a);
        }

        template <typename T>
        void RenderPoints(std::vector< Math::Vector<2,T> > &point_vec, SDL_Renderer *target,
                          SDL_Color color, float thickness = 1.f) {
            Uint8 r,g,b,a;
            SDL_GetRenderDrawColor(target, &r, &g, &b, &a);
            SDL_SetRenderDrawColor(target, color.r, color.g, color.b, color.a);

            SDL_Point pts[point_vec.size()];
            for (size_t i = 0; i < point_vec.size(); i++) {
                pts[i] = (SDL_Point)point_vec[i];
            }
            SDL_RenderDrawLines(target, pts, point_vec.size());

            SDL_SetRenderDrawColor(target, r, g, b, a);
        }

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
                          float thickness = 1.0f, unsigned int samples = Math::DEFAULT_SAMPLES) {
            std::vector< Math::Vector<2,T> > pts;
            bezier.sample(pts, samples);

            RenderPoints(pts, target, color, thickness);

            if (DEBUGGING > 1) {
                Uint8 r,g,b,a;
                SDL_GetRenderDrawColor(target, &r, &g, &b, &a);
                SDL_SetRenderDrawColor(target, 255-color.r, 255-color.g, 255-color.b, color.a);

                SDL_RenderDrawLine(target, bezier.c0[0], bezier.c0[1], bezier.p0[0], bezier.p0[1]);
                SDL_RenderDrawLine(target, bezier.c1[0], bezier.c1[1], bezier.p1[0], bezier.p1[1]);

                SDL_SetRenderDrawColor(target, r, g, b, a);

                RenderCircle(target, {0, 255, 0, 255}, bezier.p0[0], bezier.p0[1], 5);
                RenderCircle(target, {0, 255, 0, 255}, bezier.p1[0], bezier.p1[1], 5);
                RenderCircle(target, {255, 0, 0, 255}, bezier.c0[0], bezier.c0[1], 5);
                RenderCircle(target, {255, 0, 0, 255}, bezier.c1[0], bezier.c1[1], 5);
            }
        }

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
                        float thickness = 1.0f) {
            std::vector< Math::Vector<2,T> > pts;
            path.sample(pts);

            RenderPoints(pts, target, color, thickness);

            if (DEBUGGING > 1) {
                for (auto &bezier : path.get_curves()) {
                    Uint8 r,g,b,a;
                    SDL_GetRenderDrawColor(target, &r, &g, &b, &a);
                    SDL_SetRenderDrawColor(target, 255-color.r, 255-color.g, 255-color.b, color.a);

                    SDL_RenderDrawLine(target, bezier.c0[0], bezier.c0[1], bezier.p0[0], bezier.p0[1]);
                    SDL_RenderDrawLine(target, bezier.c1[0], bezier.c1[1], bezier.p1[0], bezier.p1[1]);

                    SDL_SetRenderDrawColor(target, r, g, b, a);

                    RenderCircle(target, {0, 255, 0, 255}, bezier.p0[0], bezier.p0[1], 8);
                    RenderCircle(target, {0, 255, 0, 255}, bezier.p1[0], bezier.p1[1], 8);
                    RenderCircle(target, {255, 0, 0, 255}, bezier.c0[0], bezier.c0[1], 8);
                    RenderCircle(target, {255, 0, 0, 255}, bezier.c1[0], bezier.c1[1], 8);
                }
            }
        }

    };
};

#endif // GRAPHICS_HPP
