/*
This file is part of pyOCCT which provides Python bindings to the OpenCASCADE
geometry kernel.

Copyright (C) 2016-2018  Laughlin Research, LLC
Copyright (C) 2019 Trevor Laughlin and the pyOCCT contributors

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <pyOCCT_Common.hxx>
#include <AIS_Relation.hxx>
#include <TopoDS_Shape.hxx>
#include <Standard_Handle.hxx>
#include <Geom_Plane.hxx>
#include <Standard_TypeDef.hxx>
#include <Prs3d_Projector.hxx>
#include <Geom_Transformation.hxx>
#include <Prs3d_Presentation.hxx>
#include <AIS_MidPointRelation.hxx>
#include <Standard_Type.hxx>
#include <PrsMgr_PresentationManager3d.hxx>
#include <SelectMgr_Selection.hxx>
#include <gp_Lin.hxx>
#include <gp_Pnt.hxx>
#include <gp_Circ.hxx>
#include <gp_Elips.hxx>

void bind_AIS_MidPointRelation(py::module &mod){

py::class_<AIS_MidPointRelation, opencascade::handle<AIS_MidPointRelation>, AIS_Relation> cls_AIS_MidPointRelation(mod, "AIS_MidPointRelation", "presentation of equal distance to point myMidPoint");

// Constructors
cls_AIS_MidPointRelation.def(py::init<const TopoDS_Shape &, const TopoDS_Shape &, const TopoDS_Shape &, const opencascade::handle<Geom_Plane> &>(), py::arg("aSymmTool"), py::arg("FirstShape"), py::arg("SecondShape"), py::arg("aPlane"));

// Fields

// Methods
cls_AIS_MidPointRelation.def("IsMovable", (Standard_Boolean (AIS_MidPointRelation::*)() const) &AIS_MidPointRelation::IsMovable, "None");
cls_AIS_MidPointRelation.def("SetTool", (void (AIS_MidPointRelation::*)(const TopoDS_Shape &)) &AIS_MidPointRelation::SetTool, "None", py::arg("aMidPointTool"));
cls_AIS_MidPointRelation.def("GetTool", (const TopoDS_Shape & (AIS_MidPointRelation::*)() const) &AIS_MidPointRelation::GetTool, "None");
cls_AIS_MidPointRelation.def("Compute", (void (AIS_MidPointRelation::*)(const opencascade::handle<Prs3d_Projector> &, const opencascade::handle<Geom_Transformation> &, const opencascade::handle<Prs3d_Presentation> &)) &AIS_MidPointRelation::Compute, "Computes the presentation according to a point of view given by <aProjector>. To be Used when the associated degenerated Presentations have been transformed by <aTrsf> which is not a Pure Translation. The HLR Prs can't be deducted automatically WARNING :<aTrsf> must be applied to the object to display before computation !!!", py::arg("aProjector"), py::arg("aTrsf"), py::arg("aPresentation"));
cls_AIS_MidPointRelation.def_static("get_type_name_", (const char * (*)()) &AIS_MidPointRelation::get_type_name, "None");
cls_AIS_MidPointRelation.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &AIS_MidPointRelation::get_type_descriptor, "None");
cls_AIS_MidPointRelation.def("DynamicType", (const opencascade::handle<Standard_Type> & (AIS_MidPointRelation::*)() const) &AIS_MidPointRelation::DynamicType, "None");

// Enums

}