/*
 * Copyright (c) 1995-2017, Stanford University
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Stanford University nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY STANFORD UNIVERSITY ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL STANFORD UNIVERSITY BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ZIPPER_MESHOPS_H
#define ZIPPER_MESHOPS_H

// Internal
#include "zipper.h"
#include "matrix.h"

// Declarations
void absorb_transform(Scan* sc);
void fix_bows(Scan* sc);
int fill_bow(Mesh* mesh, Vertex* vert, Vertex* vin[], Vertex* vout[], int in_out_count);
void split_triangle(Scan* sc, Triangle* tri, int index1, float t, Triangle** tri1, Triangle** tri2);
void split_test(Scan* sc);
int edges_shared_count(Vertex* v1, Vertex* v2);
Triangle* shared_triangle(int index);
void fill_small_holes(Scan* sc);
void fill_hole(Mesh* mesh, Edge* edge, int edge_count);
void fill_four_hole(Mesh* mesh, Vertex* v1, Vertex* v2, Vertex* v3, Vertex* v4);
void remove_cut_vertices(Scan* scan);
int remove_a_vertex(Scan* scan, Vertex* v);
void remove_sliver_tris(Scan* scan, float fract);
void remove_flat_verts(Scan* scan, float cos_max);
void remove_bad_aspect_tris(Scan* scan, float max_aspect, float min_cos, int diff);
void move_vertex(Vertex* v, Vector pos, Mesh* mesh);
void remove_short_edges(Scan* scan, float fract);
void collapse_edge(Mesh* mesh, Vertex* v1, Vertex* v2);
void quarter_mesh(Scan* scan);
int fill_loop(int loop, Scan* scan);
void swap_edges(Scan* sc);
void compute_smoothing(Vertex* v, Vector new_pos);
void smooth_vertices(Scan* sc);

#endif
