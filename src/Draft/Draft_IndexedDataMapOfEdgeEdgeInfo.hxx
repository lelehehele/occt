// Created on: 1994-08-31
// Created by: Jacques GOUSSARD
// Copyright (c) 1994-1999 Matra Datavision
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

#ifndef Draft_IndexedDataMapOfEdgeEdgeInfo_HeaderFile
#define Draft_IndexedDataMapOfEdgeEdgeInfo_HeaderFile

#include <TopoDS_Edge.hxx>
#include <Draft_EdgeInfo.hxx>
#include <TopTools_ShapeMapHasher.hxx>
#include <NCollection_IndexedDataMap.hxx>

typedef NCollection_IndexedDataMap<TopoDS_Edge,Draft_EdgeInfo,TopTools_ShapeMapHasher> Draft_IndexedDataMapOfEdgeEdgeInfo;


#endif
