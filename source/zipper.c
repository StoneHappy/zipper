/*

Zipper together polygon meshes derived from multiple depth scans.

Greg Turk, December 1992

---------------------------------------------------------------

Copyright (c) 1994 The Board of Trustees of The Leland Stanford
Junior University.  All rights reserved.

Permission to use, copy, modify and distribute this software and its
documentation for any purpose is hereby granted without fee, provided
that the above copyright notice and this permission notice appear in
all copies of this software and that you do not sell the software.

THE SOFTWARE IS PROVIDED "AS IS" AND WITHOUT WARRANTY OF ANY KIND,
EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>

#include "zipper.h"

/* list of scans */
Scan* scans[SCAN_MAX];
int nscans = 0;

int global_chew_count = 8;

extern int move_num;
extern Matrix rotmat;
extern Matrix transmat;

float MAX_EDGE_LENGTH_FACTOR;
float MAX_EDGE_LENGTH;

void update_edge_length_resolution()
{
    MAX_EDGE_LENGTH = ZIPPER_RESOLUTION * MAX_EDGE_LENGTH_FACTOR;
}

void set_max_edge_length_factor(float factor)
{
    MAX_EDGE_LENGTH_FACTOR = factor;
    MAX_EDGE_LENGTH = ZIPPER_RESOLUTION * MAX_EDGE_LENGTH_FACTOR;
}

float get_max_edge_length_factor()
{
    return MAX_EDGE_LENGTH_FACTOR;
}

/* The "scale" of the system; formally SPACING. */
float ZIPPER_RESOLUTION = 0.0005;

/* mesh display level */
int mesh_level = 3;

float get_zipper_resolution()
{
    return ZIPPER_RESOLUTION;
}

void init_resolution_parameters()
{
    set_max_edge_length_factor(4.0);

    set_fill_edge_length_factor(2.0);

    set_conf_edge_count_factor(1.0);
    set_conf_edge_zero(0);
    set_conf_angle(0);
    set_conf_exponent(1.0);

    set_align_near_dist_factor(2.0);
    set_align_near_cos(0.3);

    set_eat_near_dist_factor(2.0);
    set_eat_near_cos(-0.5);
    set_eat_start_iters(2);
    set_eat_start_factor(4.0);

    set_clip_near_dist_factor(2.0);
    set_clip_near_cos(0.3);
    set_clip_boundary_dist_factor(4.0);
    set_clip_boundary_cos(0.3);

    set_consensus_position_dist_factor(1.0);
    set_consensus_normal_dist_factor(3.0);
    set_consensus_jitter_dist_factor(0.01);

    /* These don't really belong under "resolution", but... */
    set_range_data_sigma_factor(4.0);
    set_range_data_min_intensity(0.05);
    set_range_data_horizontal_erode(1);
}

void set_zipper_resolution(float res)
{
    ZIPPER_RESOLUTION = res;

    update_edge_length_resolution();
    update_fill_resolution();
    update_align_resolution();
    update_eat_resolution();
    update_clip_resolution();
    update_consensus_resolution();
}


/******************************************************************************
Main routine.
******************************************************************************/
int main(int argc, char* argv[])
{
    init_resolution_parameters();

    if (argc < 4) {
        printf("Usage: zipper src1.ply src2.ply dst1.ply dst2.ply\n");
        return 0;
    }

    if (read_ply(argv[1]) != 0) {
        printf("Failed to read input 1: %s", argv[1]);
        return 1;
    }
    if (read_ply(argv[2]) != 0) {
        printf("Failed to read input 2: %s", argv[2]);
        return 1;
    }

    do_it_all();
    //clip_triangles(scans[0], scans[1]);

    write_ply(scans[0], argv[3], 1);
    write_ply(scans[1], argv[4], 1);
}

/******************************************************************************
Return how many range image positions are between each vertex at a given
mesh level.  E.g., mesh level 3 uses every 8th range image point.

Entry:
  level - level to find out about

Exit:
  returns number of range positions between vertices
******************************************************************************/

int level_to_inc(int level)
{
    switch (level) {
        case 0:
            return (1);
        case 1:
            return (2);
        case 2:
            return (4);
        case 3:
            return (8);
        default:
            fprintf(stderr, "level_to_inc: bad switch %d\n", level);
            exit(-1);
    }
}


/******************************************************************************
Return maximum length allowed for a triangle of a given level.
******************************************************************************/

float edge_length_max(int level)
{
    float max_length;
    int inc;

    /* pick how far apart the mesh samples are, based on the level of */
    /* detail requested */

    inc = level_to_inc(level);

    /* compute maximum okay length of a triangle edge */

    max_length = MAX_EDGE_LENGTH * inc;

    return (max_length);
}

/******************************************************************************
Return the number of seconds since this routine was last called.
Returns junk on first call.
******************************************************************************/

float time_it()
{
    static long int last_sec;
    static long int last_usec;
    long int sec;
    long int usec;
    struct timeval tp;
    struct timezone tzp;
    float time;

    gettimeofday(&tp, &tzp);
    sec = tp.tv_sec - last_sec;
    usec = tp.tv_usec - last_usec;
    last_sec = tp.tv_sec;
    last_usec = tp.tv_usec;

    if (usec < 0)
        time = (sec - 1) + (usec + 1000000) / 1000000.0;
    else
        time = sec + usec / 1000000.0;

    return (time);
}


/******************************************************************************
Print the positions of all meshes.
******************************************************************************/

#if 0
void print_positions(fp)
FILE* fp;
{
    int i, j, k;
    Quaternion quat;
    Matrix mat;

    /* print viewing parameters */
    mat_to_quat(rotmat, quat);

    fprintf(fp, "camera %g %g %g  %g %g %g %g\n",
            transmat[3][0], transmat[3][1], transmat[3][2],
            quat[0], quat[1], quat[2], quat[3]);

    /* print quaternion version */

    for (i = 0; i < nscans; i++) {
        mat_to_quat(scans[i]->rotmat, quat);
        if (scans[i]->file_type == POLYFILE)
            fprintf(fp, "bpolygon ");
        else if (scans[i]->file_type == RAWFILE)
            fprintf(fp, "rmesh ");
        else if (scans[i]->file_type == PLYRANGEFILE)
            fprintf(fp, "bmesh ");
        else
            fprintf(fp, "mesh ");
        fprintf(fp, "%s %g %g %g %g %g %g %g\n", scans[i]->name,
                scans[i]->xtrans, scans[i]->ytrans, scans[i]->ztrans,
                quat[0], quat[1], quat[2], quat[3]);
    }
    fprintf(fp, "\n");
}
#endif

/******************************************************************************
Print the positions of all meshes in matrix form.
******************************************************************************/

#if 0
void print_mat_positions(fp)
FILE* fp;
{
    int i, j, k;
    Quaternion quat;
    Matrix mat, imat;
    float det;

    /* print viewing parameters */
    mat_to_quat(rotmat, quat);
    fprintf(fp, "Number of meshes:  %d\n", nscans);
    fprintf(fp, "camera %g %g %g  %g %g %g %g\n",
            transmat[3][0], transmat[3][1], transmat[3][2],
            quat[0], quat[1], quat[2], quat[3]);

    /* print matrix version */

    fprintf(fp, "\n");
    for (i = 0; i < nscans; i++) {
        fprintf(fp, "%s:\n", scans[i]->name);

        /* compute the tranformation matrix */
        mat_translate(mat, scans[i]->xtrans, scans[i]->ytrans, scans[i]->ztrans);
        mat_mult(mat, mat, scans[i]->rotmat);

        /* inverse of mat */
        mat_copy(imat, mat);
        det = mat_invert(imat);

        fprintf(fp, "matrix:\n");
        for (j = 0; j <= 3; j++) {
            for (k = 0; k <= 3; k++)
                fprintf(fp, "%f  ", mat[k][j]);
            fprintf(fp, "\n");
        }
        fprintf(fp, "\n");

        fprintf(fp, "inverse matrix:\n");
        for (j = 0; j <= 3; j++) {
            for (k = 0; k <= 3; k++)
                fprintf(fp, "%f  ", imat[k][j]);
            fprintf(fp, "\n");
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "\n");
}
#endif

/******************************************************************************
Create all the meshes for the current level of detail.
******************************************************************************/
void create_current_level()
{
    int i;
    for (i = 0; i < nscans; i++)
        create_scan_mesh(scans[i], mesh_level);
}
