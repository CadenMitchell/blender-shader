/**
* $Id$ 
*
* ***** BEGIN GPL LICENSE BLOCK *****
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software Foundation,
* Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*
* The Original Code is Copyright (C) 2001-2002 by NaN Holding BV.
* All rights reserved.
*
* The Original Code is: all of this file.
*
* Contributor(s): none yet.
*
* ***** END GPL LICENSE BLOCK *****
*/

#ifndef NAVMESH_CONVERSION_H
#define NAVMESH_CONVERSION_H

#ifdef __cplusplus
extern "C" {
#endif

struct DerivedMesh;

/* navmesh_conversion.cpp */
bool buildNavMeshDataByDerivedMesh(DerivedMesh *dm, int& vertsPerPoly, 
								   int &nverts, float *&verts,
								   int &ndtris, unsigned short *&dtris,
								   int& npolys, unsigned short *&dmeshes,
								   unsigned short*& polys, int *&dtrisToPolysMap,
								   int *&dtrisToTrisMap, int *&trisToFacesMap);

bool buildRawVertIndicesData(DerivedMesh* dm, int &nverts, float *&verts, 
				int &ntris, unsigned short *&tris, int *&trisToFacesMap,
				int *&recastData);

bool buildNavMeshData(const int nverts, const float* verts, 
					  const int ntris, const unsigned short *tris, 
					  const int* recastData, const int* trisToFacesMap,
					  int &ndtris, unsigned short *&dtris,
					  int &npolys, unsigned short *&dmeshes, unsigned short *&polys,
					  int &vertsPerPoly, int *&dtrisToPolysMap, int *&dtrisToTrisMap);

bool buildPolygonsByDetailedMeshes(const int vertsPerPoly, const int npolys, 
				unsigned short* polys, const unsigned short* dmeshes, 
				const float* verts, const unsigned short* dtris, 
				const int* dtrisToPolysMap);

int polyNumVerts(const unsigned short* p, const int vertsPerPoly);
bool polyIsConvex(const unsigned short* p, const int vertsPerPoly, const float* verts);
int polyFindVertex(const unsigned short* p, const int vertsPerPoly, unsigned short vertexIdx);
float distPointToSegmentSq(const float* point, const float* a, const float* b);


inline int bit(int a, int b)
{
	return (a & (1 << b)) >> b;
}

inline void intToCol(int i, float* col)
{
	int	r = bit(i, 0) + bit(i, 3) * 2 + 1;
	int	g = bit(i, 1) + bit(i, 4) * 2 + 1;
	int	b = bit(i, 2) + bit(i, 5) * 2 + 1;
	col[0] = 1 - r*63.0f/255.0f;
	col[1] = 1 - g*63.0f/255.0f;
	col[2] = 1 - b*63.0f/255.0f;
}

inline float area2(const float* a, const float* b, const float* c)
{
	return (b[0] - a[0]) * (c[2] - a[2]) - (c[0] - a[0]) * (b[2] - a[2]);
}
inline bool left(const float* a, const float* b, const float* c)
{
	return area2(a, b, c) < 0;
}

#ifdef __cplusplus
}
#endif
#endif //NAVMESH_CONVERSION_H
