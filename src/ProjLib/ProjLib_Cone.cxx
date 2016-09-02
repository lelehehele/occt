// Created on: 1993-08-24
// Created by: Bruno DUMORTIER
// Copyright (c) 1993-1999 Matra Datavision
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


#include <ElSLib.hxx>
#include <gp.hxx>
#include <gp_Circ.hxx>
#include <gp_Cone.hxx>
#include <gp_Elips.hxx>
#include <gp_Hypr.hxx>
#include <gp_Lin.hxx>
#include <gp_Parab.hxx>
#include <gp_Trsf.hxx>
#include <gp_Vec.hxx>
#include <gp_Vec2d.hxx>
#include <Precision.hxx>
#include <ProjLib_Cone.hxx>
#include <Standard_NoSuchObject.hxx>

//=======================================================================
//function : ProjLib_Cone
//purpose  : 
//=======================================================================
ProjLib_Cone::ProjLib_Cone()
{
}


//=======================================================================
//function : ProjLib_Cone
//purpose  : 
//=======================================================================

ProjLib_Cone::ProjLib_Cone(const gp_Cone& Co)
{
  Init(Co);
}


//=======================================================================
//function : ProjLib_Cone
//purpose  : 
//=======================================================================

ProjLib_Cone::ProjLib_Cone(const gp_Cone& Co, const gp_Lin& L)
{
  Init(Co);
  Project(L);
}


//=======================================================================
//function : ProjLib_Cone
//purpose  : 
//=======================================================================

ProjLib_Cone::ProjLib_Cone(const gp_Cone& Co, const gp_Circ& C)
{
  Init(Co);
  Project(C);
}


//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void  ProjLib_Cone::Init(const gp_Cone& Co)
{
  myType = GeomAbs_OtherCurve;
  myCone = Co;
  myIsPeriodic = Standard_False;
  isDone = Standard_False;
}

//=======================================================================
//function : Project
//purpose  : 
//=======================================================================

void  ProjLib_Cone::Project(const gp_Lin& L)
{

  Standard_Real U,V;
  
  // Compute V
  V = gp_Vec(myCone.Location(),L.Location())
    .Dot(gp_Vec(myCone.Position().Direction()));
  V /= Cos( myCone.SemiAngle());

  // Compute U
  gp_Ax3 CPos  = myCone.Position();
  gp_Dir ZCone = CPos.XDirection() ^ CPos.YDirection();
  
  gp_Ax3 RightHanded(CPos.Location(), ZCone, CPos.XDirection());
  gp_Trsf T;
  T.SetTransformation(RightHanded);

  gp_Dir D = L.Position().Direction();
  D.Transform(T);

  if ( D.Z() < 0.) D.Reverse();
  D.SetCoord(3, 0.);
  U = gp::DX().AngleWithRef( D, gp::DZ());

  Standard_Integer a1 = 
    (ZCone.IsEqual(CPos.Direction(), Precision::Angular())) ? 1 : -1;
  Standard_Integer a2 = 
    (myCone.SemiAngle() > 0) ? 1 : -1;
  if ( ( a1 * a2) == -1) U -= M_PI;

  if ( U < 0.) U += 2.*M_PI;

  gp_Pnt P;
  gp_Vec Vu, Vv;

  ElSLib::ConeD1(U, V, CPos, myCone.RefRadius(), myCone.SemiAngle(),
		 P, Vu, Vv);

  if(Vv.IsParallel(gp_Vec(L.Position().Direction()), Precision::Angular())) {

    myType = GeomAbs_Line;

    gp_Pnt2d P2d(U,V);
  
    Standard_Real Signe = L.Direction().Dot(myCone.Position().Direction());
    Signe = (Signe > 0.) ? 1. : -1.;
    gp_Dir2d D2d(0., Signe);
  
    myLin = gp_Lin2d( P2d, D2d);

    isDone = Standard_True;
  }
    
}


//=======================================================================
//function : Project
//purpose  : 
//=======================================================================

void  ProjLib_Cone::Project(const gp_Circ& C)
{
  myType = GeomAbs_Line;

  gp_Ax3 ConePos = myCone.Position();
  gp_Ax3 CircPos = C.Position();

  gp_Dir ZCone = ConePos.XDirection().Crossed(ConePos.YDirection());
  gp_Dir ZCir =  CircPos.XDirection().Crossed(CircPos.YDirection());

  Standard_Real U, V;
  Standard_Real x = ConePos.XDirection().Dot(CircPos.XDirection());
  Standard_Real y = ConePos.YDirection().Dot(CircPos.XDirection());
  Standard_Real z 
    = gp_Vec(myCone.Location(),C.Location()).Dot(ConePos.Direction());
  
  // pour trouver le point U V, on reprend le code de ElSLib
  // sans appliquer la Trsf au point ( aller retour inutile).
  if ( x == 0.0 && y == 0.0 ) {
    U = 0.;
  }
  else if ( -myCone.RefRadius() > z * Tan(myCone.SemiAngle())) {
    U = ATan2(-y, -x);
  }
  else {
    U = ATan2( y, x);
  }
  if ( U < 0.) U += 2*M_PI;

  V = z / Cos(myCone.SemiAngle());

  gp_Pnt2d P2d1 (U, V);
  gp_Dir2d D2d;
  if ( ZCone.Dot(ZCir) > 0.) 
    D2d.SetCoord(1., 0.);
  else
    D2d.SetCoord(-1., 0.);

  myLin = gp_Lin2d(P2d1, D2d);
  isDone = Standard_True;
}

void  ProjLib_Cone::Project(const gp_Elips& E)
{
  ProjLib_Projector::Project(E);
}

void  ProjLib_Cone::Project(const gp_Parab& P)
{
 ProjLib_Projector::Project(P);
}

void  ProjLib_Cone::Project(const gp_Hypr& H)
{
 ProjLib_Projector::Project(H);
}

