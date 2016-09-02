// Created on: 2013-12-25
// Created by: Varvara POSKONINA
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _OpenGl_BVHTreeSelector_HeaderFile
#define _OpenGl_BVHTreeSelector_HeaderFile

#include <Graphic3d_Camera.hxx>
#include <Graphic3d_WorldViewProjState.hxx>
#include <OpenGl_Vec.hxx>

//! BVHTreeSelector class provides a possibility to store parameters of view volume,
//! such as its vertices and equations, and contains methods detecting if given AABB overlaps
//! view volume.
class OpenGl_BVHTreeSelector
{
public:

  //! Creates an empty selector object with parallel projection type by default.
  Standard_EXPORT OpenGl_BVHTreeSelector();

  //! Retrieves view volume's planes equations and its vertices from projection and world-view matrices.
  Standard_EXPORT void SetViewVolume (const Handle(Graphic3d_Camera)& theCamera);

  //! Detects if AABB overlaps view volume using separating axis theorem (SAT).
  //! @param theMinPt [in] maximum point of AABB.
  //! @param theMaxPt [in] minimum point of AABB.
  //! @return Standard_True, if AABB is in viewing area, Standard_False otherwise.
  Standard_EXPORT Standard_Boolean Intersect (const OpenGl_Vec4& theMinPt,
                                              const OpenGl_Vec4& theMaxPt) const;

  //! Caches view volume's vertices projections along its normals and AABBs dimensions.
  //! Must be called at the beginning of each BVH tree traverse loop.
  Standard_EXPORT void CacheClipPtsProjections();

  //! Returns current projection matrix.
  const OpenGl_Mat4& ProjectionMatrix() const
  {
    return myProjectionMat;
  }

  //! Returns current world view transformation matrix.
  const OpenGl_Mat4& WorldViewMatrix() const
  {
    return myWorldViewMat;
  }

  //! Returns state of current world view projection transformation matrices.
  const Graphic3d_WorldViewProjState& WorldViewProjState() const
  {
    return myWorldViewProjState;
  }

protected:

  //! Calculates signed distance from plane to point.
  //! @param theNormal [in] the plane's normal.
  //! @param thePnt    [in]
  Standard_EXPORT Standard_ShortReal SignedPlanePointDistance (const OpenGl_Vec4& theNormal,
                                                               const OpenGl_Vec4& thePnt);

protected:

  //! Enumerates planes of view volume.
  enum
  {
    Plane_Top,
    Plane_Bottom,
    Plane_Left,
    Plane_Right,
    Plane_Near,
    Plane_Far,
    PlanesNB
  };

  //! Enumerates vertices of view volume.
  enum
  {
    ClipVert_LeftTopNear,
    ClipVert_LeftBottomNear,
    ClipVert_RightTopNear,
    ClipVert_RightBottomNear,
    ClipVert_LeftTopFar,
    ClipVert_LeftBottomFar,
    ClipVert_RightTopFar,
    ClipVert_RightBottomFar,
    ClipVerticesNB
  };

protected:

  OpenGl_Vec4 myClipPlanes[PlanesNB];      //!< Plane equations
  OpenGl_Vec4 myClipVerts[ClipVerticesNB]; //!< Vertices

  // for caching clip points projections onto viewing area normals once per traverse
  // ORDER: TOP, BOTTOM, LEFT, RIGHT, NEAR, FAR
  Standard_ShortReal myMaxClipProjectionPts[PlanesNB]; //!< Max view volume's vertices projections onto its normals
  Standard_ShortReal myMinClipProjectionPts[PlanesNB]; //!< Min view volume's vertices projections onto its normals

  // for caching clip points projections onto AABB normals once per traverse
  // ORDER: E0, E1, E2
  Standard_ShortReal myMaxOrthoProjectionPts[3]; //!< Max view volume's vertices projections onto normalized dimensions of AABB
  Standard_ShortReal myMinOrthoProjectionPts[3]; //!< Min view volume's vertices projections onto normalized dimensions of AABB

  Standard_Boolean myIsProjectionParallel;

  OpenGl_Mat4 myProjectionMat;
  OpenGl_Mat4 myWorldViewMat;

  Graphic3d_WorldViewProjState myWorldViewProjState; //!< State of world view projection matrices.
};

#endif // _OpenGl_BVHTreeSelector_HeaderFile
