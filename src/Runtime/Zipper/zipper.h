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

#ifndef ZIPPER_ZIPPER_H
#define ZIPPER_ZIPPER_H

// External
#include <limits.h>

// Internal
#include "matrix.h"
#define PATH_MAX 260
// Macros
#define MAX(a,b)    ((a)>(b)?(a):(b))       /* return greater of a and b */
#define MIN(a,b)    ((a)<(b)?(a):(b))       /* return lesser of a and b */

struct Triangle;
struct Mesh;
struct Edge;
struct Clipped_Edge;
struct More_Tri_Stuff;
struct Cinfo;
struct Cut;
struct FillTri;
struct RawData;
struct RangeData;

typedef struct Vertex {     /* vertex for a mesh of triangles */
    Vector coord;         /* position */
    Vector normal;        /* surface normal */
    struct Triangle** tris;   /* list of triangles that share this vertex */
    struct Vertex** verts;    /* list of vertices that share an edge */
    struct Edge** edges;      /* list of edges for vertex */
    unsigned char on_edge;    /* flag: is vertex on edge of mesh? */
    unsigned char count;      /* used to determine if vertex is on edge */
    unsigned char ntris;      /* number of triangles in list */
    unsigned char max_tris;   /* current maximum # of triangles in list */
    unsigned char nverts;     /* number of vertices in list */
    unsigned char max_verts;  /* current maximum # of vertices in list */
    unsigned char nedges;     /* number of edges in list */
    unsigned char max_edges;  /* current maximum number of edges in list */
    unsigned char moving;     /* is vertex being moved to another mesh? */
    unsigned char red, grn, blu;  /* color at the vertex */
    float confidence;     /* confidence about the position of vertex */
    float intensity;      /* intensity at vertex */
    struct Cinfo* cinfo;      /* consensus geometry info */
    struct Mesh* old_mesh;    /* mesh this vertex used to belong to */
    struct Vertex* move_to;   /* for moving vertex to another mesh */
    struct Vertex* next;      /* for linked list */
    int index;            /* position of vertex in mesh array */
} Vertex;

typedef struct Triangle {   /* triangle in a mesh */
    Vertex* verts[3];     /* vertices of triangle */
    float a[3], b[3], c[3], d[3]; /* plane equations for edges */
    float aa, bb, cc, dd;     /* plane equation containing triangle */
    int index;            /* position of triangle in mesh array */
    struct Clipped_Edge* clips;   /* where tri is clipped (list of 3 (edges)) */
    struct More_Tri_Stuff* more;  /* double-precision numbers for clipping */
    unsigned char mark, eat_mark; /* flags */
    unsigned char dont_touch; /* don't touch this triangle during eating */
} Triangle;

typedef struct More_Tri_Stuff {
    double a[3], b[3], c[3], d[3]; /* plane equations for edges */
    double aa, bb, cc, dd;    /* plane equation containing triangle */
    Vertex* mids[3];      /* mid-points for quartering a triangle */
    struct Cut** cuts;        /* list of intersection points of triangle */
    int cut_num;          /* number of cuts in list */
    int cut_max;          /* maximum number of cuts in list */
    Vertex** clip_verts;      /* list of vertices to make clipped triangle */
    unsigned char clip_count; /* number of vertices in clip_verts */
    unsigned char clip_flag;  /* whether this triangle gets clipped */
    struct FillTri* fill_tri; /* pointer to fill triangle (if one exists) */
} More_Tri_Stuff;

#define PR1  17
#define PR2 101
#define TABLE_SIZE1  5003
#define TABLE_SIZE2 17003
#define TABLE_SIZE3 53003

typedef struct Hash_Table { /* uniform spatial subdivision, with hash */
    int npoints;          /* number of points placed in table */
    Vertex** verts;       /* array of hash cells */
    int num_entries;      /* number of array elements in verts */
    float scale;          /* size of cell */
} Hash_Table;

/* where a segment of a triangle cuts an edge of a mesh or */
/* a triangle (depending if we're in clip.c or intersect.c, resp. */

typedef struct Cut {
    Vertex* v1, *v2;      /* endpoints of segment that cut an edge */
    struct Edge* edge;        /* edge that was cut */
    struct Triangle* tri;     /* triangle that was intersected */
    Vertex* new_vert;     /* new vertex created by this cut (eventually)*/
    float t;          /* parameter saying where edge was cut */
    float s;          /* parameter along segment v1 - v2 */
    unsigned char inward;     /* whether segment is directed into the mesh */
    unsigned char first;      /* if cut is before partner along edge loop */
    struct Cut* partner;      /* other cut that helps divide this triangle */
    float dot;            /* dot product between intersecting tris */
} Cut;

typedef struct Clipped_Edge {   /* the three clipped edges of a triangle */
    Vertex* v1, *v2;      /* vertices that define this edge */
    Triangle* t1, *t2;    /* triangle(s) that edge belongs to */
    Cut** cuts;           /* list of cut points along edge */
    unsigned char cut_num;    /* number of cuts in list */
    unsigned char cut_max;    /* maximum number of cuts in list */
    unsigned char perp_intersect; /* is this from a perpendicular intersection? */
    unsigned char done_edge;  /* have we examined this edge? */
} Clipped_Edge;

typedef struct Edge {
    Vertex* v1, *v2;      /* vertices that make up the edge */
    Triangle* tri;        /* triangle that edge belongs to */
    Triangle* t[4];       /* triangles for clipping */
    unsigned char used;       /* is edge in the loop list? */
    unsigned char num;        /* number of this edge's loop */
    struct Edge* prev;        /* pointer to previous edge in loop */
    struct Edge* next;        /* pointer to next edge in loop */
    Cut** cuts;           /* list of cut points of edge */
    int cut_num;          /* number of cuts in list */
    int cut_max;          /* maximum number of cuts in list */
} Edge;

#define LOOP_MAX 3000

typedef struct EdgeLoop {
    int nloops;
    Edge* loops[LOOP_MAX];
} EdgeLoop;

typedef struct Mesh {       /* mesh of triangles */
    Triangle** tris;      /* list of triangles */
    int ntris;            /* number of triangles */
    int max_tris;         /* maximum number of triangles in list */
    Vertex** verts;       /* list of vertices */
    int nverts;           /* number of vertices */
    int max_verts;        /* maximum number of vertices in list */
    Edge** edges;         /* list of edges */
    int nedges;           /* number of edges */
    int max_edges;        /* maximum number of edges in list */
    EdgeLoop looplist;        /* edge loops */
    int edges_valid;      /* are the edges correct? */
    Hash_Table* table;        /* structure for nearest neighbor search */
    Triangle** eat_list;      /* helper list for eating away edges */
    int eat_list_num;     /* number of tris in eat_list */
    int eat_list_max;     /* maximum number of tris in eat_list */
    struct Scan* parent_scan; /* which scan this mesh belongs to */
} Mesh;

#define MAX_MESH_LEVELS 4
typedef struct Scan {       /* information about one depth scan */
    char name[80];        /* name of scan */
    int button_index;             /* number used to refer to TCL buttons */
    struct RawData* raw_geom; /* geometry if read from a raw file */
    struct RangeData* ply_geom;   /* geometry if read from a PLY file */
    float* sin_theta;     /* tables for speedy drawing */
    float* cos_theta;
    float xtrans, ytrans, ztrans; /* translation */
    float rotate;         /* rotation around y-axis */
    Matrix rotmat;        /* rotation matrix */
    int draw_flag;        /* whether to draw this scan */
    Mesh* meshes[MAX_MESH_LEVELS];/* triangle meshes (different detail levels) */
    Mesh* edge_mesh;      /* triangles for edge clipping */
    int file_type;        /* CYFILE, POLYFILE or RAWFILE? */
    char obj_info[50][PATH_MAX];  /* Beware the arbitrary "50"!! */
    int num_obj_info;
} Scan;

/* file types for meshes */
#define CYFILE        1 // REMOVED
#define POLYFILE      2
#define RAWFILE       3
#define PLYRANGEFILE  4

/* near position on another mesh */
#define NEAR_VERTEX   1
#define NEAR_EDGE     2
#define NEAR_TRIANGLE 3

typedef struct NearPosition {
    Vector pos;           /* the nearest position */
    float dist;           /* distance to nearest position */
    int type;         /* vertex, edge or triangle is nearest */
    Vertex* v1, *v2;      /* vertices involved */
    Triangle* tri;        /* triangle involved */
    int on_edge;          /* on the edge of the mesh? */
    float confidence;     /* confidence about errors of the positions */
    float b1, b2, b3;             /* weights of vertices defining intersection */
} NearPosition;

/* Clipping Structures */
typedef struct Clip_Vertex {
    unsigned char type;           /* mesh 1, 2 or cut vertex */
    unsigned char inward;         /* whether this segment points into mesh */
    unsigned char side_index;     /* side (0, 1, 2) that this vertex came from */
    Vertex* vert;                 /* pointer to vertex if it is from old mesh */
    Cut* cut;                     /* pointer to cut, if vertex is from a cut */
} Clip_Vertex;

typedef struct Clip_List {
    Clip_Vertex* list;            /* list of vertices */
    int count;                    /* number of vertices in list */
} Clip_List;

/* typical allowed value for dot product between surfaces in neighbor searches */
#define FIND_COS  0.3

// Globals
extern Scan* scans[];
extern int nscans;
extern float ZIPPER_RESOLUTION;
extern int mesh_level;

// Parameters
void update_edge_length_resolution();
void set_max_edge_length_factor(float factor);
float get_max_edge_length_factor();
float get_zipper_resolution();
void set_zipper_resolution(float res);

// Declarations
int level_to_inc(int level);
float edge_length_max(int level);
void create_current_level();

#endif
