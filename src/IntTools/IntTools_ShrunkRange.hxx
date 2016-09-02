// Created by: Peter KURNEV
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

#ifndef _IntTools_ShrunkRange_HeaderFile
#define _IntTools_ShrunkRange_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Handle.hxx>

#include <TopoDS_Edge.hxx>
#include <TopoDS_Vertex.hxx>
#include <Standard_Real.hxx>
#include <Bnd_Box.hxx>
#include <Standard_Integer.hxx>
class IntTools_Context;
class TopoDS_Edge;
class TopoDS_Vertex;
class Bnd_Box;



//! The class provides the computation of
//! a working (shrunk) range [t1, t2] for
//! the 3D-curve of the edge.
class IntTools_ShrunkRange 
{
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT IntTools_ShrunkRange();
Standard_EXPORT virtual ~IntTools_ShrunkRange();
  
  Standard_EXPORT void SetData (const TopoDS_Edge& aE, const Standard_Real aT1, const Standard_Real aT2, const TopoDS_Vertex& aV1, const TopoDS_Vertex& aV2);
  
  Standard_EXPORT void SetContext (const Handle(IntTools_Context)& aCtx);
  
  Standard_EXPORT const Handle(IntTools_Context)& Context() const;
  
  Standard_EXPORT void SetShrunkRange (const Standard_Real aT1, const Standard_Real aT2);
  
  Standard_EXPORT void ShrunkRange (Standard_Real& aT1, Standard_Real& aT2) const;
  
  Standard_EXPORT const Bnd_Box& BndBox() const;
  
  Standard_EXPORT const TopoDS_Edge& Edge() const;
  
  Standard_EXPORT void Perform();
  

  //! Returns code of computing shrunk range
  //! completion
  //! 0 - means successful completion
  //! 1 - nothing has been done
  //! 2 - initial range is out of edge's range
  //! 3 - first boundary of initial range is more than
  //! last boundary
  //! 4 - projection of first vertex failed
  //! 5 - projection of second vertex failed
  //! 6 - shrunk range can not be computed
  //! shrunk range is setted to initial range
  Standard_EXPORT Standard_Integer ErrorStatus() const;




protected:



  TopoDS_Edge myEdge;
  TopoDS_Vertex myV1;
  TopoDS_Vertex myV2;
  Standard_Real myT1;
  Standard_Real myT2;
  Standard_Real myTS1;
  Standard_Real myTS2;
  Bnd_Box myBndBox;
  Handle(IntTools_Context) myCtx;
  Standard_Integer myErrorStatus;


private:





};







#endif // _IntTools_ShrunkRange_HeaderFile
