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
#include <BRepBuilderAPI_MakeShape.hxx>
#include <Standard.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopoDS_Shape.hxx>
#include <Standard_TypeDef.hxx>
#include <TColGeom_SequenceOfCurve.hxx>
#include <Standard_Handle.hxx>
#include <Geom_Curve.hxx>
#include <BRepFeat_StatusError.hxx>
#include <LocOpe_Gluer.hxx>
#include <BRepAlgoAPI_BooleanOperation.hxx>
#include <TopTools_DataMapOfShapeListOfShape.hxx>
#include <BRepFeat_PerfSelection.hxx>
#include <TopoDS_Face.hxx>
#include <TopTools_DataMapOfShapeShape.hxx>
#include <BRepFeat_Form.hxx>

void bind_BRepFeat_Form(py::module &mod){

py::class_<BRepFeat_Form, std::unique_ptr<BRepFeat_Form, Deleter<BRepFeat_Form>>, BRepBuilderAPI_MakeShape> cls_BRepFeat_Form(mod, "BRepFeat_Form", "Provides general functions to build form features. Form features can be depressions or protrusions and include the following types: - Cylinder - Draft Prism - Prism - Revolved feature - Pipe In each case, you have a choice of operation type between the following: - removing matter (a Boolean cut: Fuse setting 0) - adding matter (Boolean fusion: Fuse setting 1) The semantics of form feature creation is based on the construction of shapes: - along a length - up to a limiting face - from a limiting face to a height - above and/or below a plane The shape defining construction of the feature can be either the supporting edge or the concerned area of a face. In case of the supporting edge, this contour can be attached to a face of the basis shape by binding. When the contour is bound to this face, the information that the contour will slide on the face becomes available to the relevant class methods. In case of the concerned area of a face, you could, for example, cut it out and move it to a different height which will define the limiting face of a protrusion or depression. Topological definition with local operations of this sort makes calculations simpler and faster than a global operation. The latter would entail a second phase of removing unwanted matter to get the same result.");

// Fields

// Methods
// cls_BRepFeat_Form.def_static("operator new_", (void * (*)(size_t)) &BRepFeat_Form::operator new, "None", py::arg("theSize"));
// cls_BRepFeat_Form.def_static("operator delete_", (void (*)(void *)) &BRepFeat_Form::operator delete, "None", py::arg("theAddress"));
// cls_BRepFeat_Form.def_static("operator new[]_", (void * (*)(size_t)) &BRepFeat_Form::operator new[], "None", py::arg("theSize"));
// cls_BRepFeat_Form.def_static("operator delete[]_", (void (*)(void *)) &BRepFeat_Form::operator delete[], "None", py::arg("theAddress"));
// cls_BRepFeat_Form.def_static("operator new_", (void * (*)(size_t, void *)) &BRepFeat_Form::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepFeat_Form.def_static("operator delete_", (void (*)(void *, void *)) &BRepFeat_Form::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepFeat_Form.def("Modified", (const TopTools_ListOfShape & (BRepFeat_Form::*)(const TopoDS_Shape &)) &BRepFeat_Form::Modified, "returns the list of generated Faces.", py::arg("F"));
cls_BRepFeat_Form.def("Generated", (const TopTools_ListOfShape & (BRepFeat_Form::*)(const TopoDS_Shape &)) &BRepFeat_Form::Generated, "returns a list of the created faces from the shape <S>.", py::arg("S"));
cls_BRepFeat_Form.def("IsDeleted", (Standard_Boolean (BRepFeat_Form::*)(const TopoDS_Shape &)) &BRepFeat_Form::IsDeleted, "None", py::arg("S"));
cls_BRepFeat_Form.def("FirstShape", (const TopTools_ListOfShape & (BRepFeat_Form::*)() const) &BRepFeat_Form::FirstShape, "Returns the list of shapes created at the bottom of the created form. It may be an empty list.");
cls_BRepFeat_Form.def("LastShape", (const TopTools_ListOfShape & (BRepFeat_Form::*)() const) &BRepFeat_Form::LastShape, "Returns the list of shapes created at the top of the created form. It may be an empty list.");
cls_BRepFeat_Form.def("NewEdges", (const TopTools_ListOfShape & (BRepFeat_Form::*)() const) &BRepFeat_Form::NewEdges, "Returns a list of the limiting and glueing edges generated by the feature. These edges did not originally exist in the basis shape. The list provides the information necessary for subsequent addition of fillets. It may be an empty list.");
cls_BRepFeat_Form.def("TgtEdges", (const TopTools_ListOfShape & (BRepFeat_Form::*)() const) &BRepFeat_Form::TgtEdges, "Returns a list of the tangent edges among the limiting and glueing edges generated by the feature. These edges did not originally exist in the basis shape and are tangent to the face against which the feature is built. The list provides the information necessary for subsequent addition of fillets. It may be an empty list. If an edge is tangent, no fillet is possible, and the edge must subsequently be removed if you want to add a fillet.");
cls_BRepFeat_Form.def("BasisShapeValid", (void (BRepFeat_Form::*)()) &BRepFeat_Form::BasisShapeValid, "Initializes the topological construction if the basis shape is present.");
cls_BRepFeat_Form.def("GeneratedShapeValid", (void (BRepFeat_Form::*)()) &BRepFeat_Form::GeneratedShapeValid, "Initializes the topological construction if the generated shape S is present.");
cls_BRepFeat_Form.def("ShapeFromValid", (void (BRepFeat_Form::*)()) &BRepFeat_Form::ShapeFromValid, "Initializes the topological construction if the shape is present from the specified integer on.");
cls_BRepFeat_Form.def("ShapeUntilValid", (void (BRepFeat_Form::*)()) &BRepFeat_Form::ShapeUntilValid, "Initializes the topological construction if the shape is present until the specified integer.");
cls_BRepFeat_Form.def("GluedFacesValid", (void (BRepFeat_Form::*)()) &BRepFeat_Form::GluedFacesValid, "Initializes the topological construction if the glued face is present.");
cls_BRepFeat_Form.def("SketchFaceValid", (void (BRepFeat_Form::*)()) &BRepFeat_Form::SketchFaceValid, "Initializes the topological construction if the sketch face is present. If the sketch face is inside the basis shape, local operations such as glueing can be performed.");
cls_BRepFeat_Form.def("PerfSelectionValid", (void (BRepFeat_Form::*)()) &BRepFeat_Form::PerfSelectionValid, "Initializes the topological construction if the selected face is present.");
cls_BRepFeat_Form.def("Curves", (void (BRepFeat_Form::*)(TColGeom_SequenceOfCurve &)) &BRepFeat_Form::Curves, "None", py::arg("S"));
cls_BRepFeat_Form.def("BarycCurve", (opencascade::handle<Geom_Curve> (BRepFeat_Form::*)()) &BRepFeat_Form::BarycCurve, "None");
cls_BRepFeat_Form.def("CurrentStatusError", (BRepFeat_StatusError (BRepFeat_Form::*)() const) &BRepFeat_Form::CurrentStatusError, "None");

// Enums

}