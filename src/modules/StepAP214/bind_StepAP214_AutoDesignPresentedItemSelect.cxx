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
#include <StepData_SelectType.hxx>
#include <Standard.hxx>
#include <Standard_TypeDef.hxx>
#include <Standard_Handle.hxx>
#include <Standard_Transient.hxx>
#include <StepBasic_ProductDefinitionRelationship.hxx>
#include <StepBasic_ProductDefinition.hxx>
#include <StepRepr_ProductDefinitionShape.hxx>
#include <StepRepr_RepresentationRelationship.hxx>
#include <StepRepr_ShapeAspect.hxx>
#include <StepBasic_DocumentRelationship.hxx>
#include <StepAP214_AutoDesignPresentedItemSelect.hxx>

void bind_StepAP214_AutoDesignPresentedItemSelect(py::module &mod){

py::class_<StepAP214_AutoDesignPresentedItemSelect, std::unique_ptr<StepAP214_AutoDesignPresentedItemSelect, Deleter<StepAP214_AutoDesignPresentedItemSelect>>, StepData_SelectType> cls_StepAP214_AutoDesignPresentedItemSelect(mod, "StepAP214_AutoDesignPresentedItemSelect", "None");

// Constructors
cls_StepAP214_AutoDesignPresentedItemSelect.def(py::init<>());

// Fields

// Methods
// cls_StepAP214_AutoDesignPresentedItemSelect.def_static("operator new_", (void * (*)(size_t)) &StepAP214_AutoDesignPresentedItemSelect::operator new, "None", py::arg("theSize"));
// cls_StepAP214_AutoDesignPresentedItemSelect.def_static("operator delete_", (void (*)(void *)) &StepAP214_AutoDesignPresentedItemSelect::operator delete, "None", py::arg("theAddress"));
// cls_StepAP214_AutoDesignPresentedItemSelect.def_static("operator new[]_", (void * (*)(size_t)) &StepAP214_AutoDesignPresentedItemSelect::operator new[], "None", py::arg("theSize"));
// cls_StepAP214_AutoDesignPresentedItemSelect.def_static("operator delete[]_", (void (*)(void *)) &StepAP214_AutoDesignPresentedItemSelect::operator delete[], "None", py::arg("theAddress"));
// cls_StepAP214_AutoDesignPresentedItemSelect.def_static("operator new_", (void * (*)(size_t, void *)) &StepAP214_AutoDesignPresentedItemSelect::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepAP214_AutoDesignPresentedItemSelect.def_static("operator delete_", (void (*)(void *, void *)) &StepAP214_AutoDesignPresentedItemSelect::operator delete, "None", py::arg(""), py::arg(""));
cls_StepAP214_AutoDesignPresentedItemSelect.def("CaseNum", (Standard_Integer (StepAP214_AutoDesignPresentedItemSelect::*)(const opencascade::handle<Standard_Transient> &) const) &StepAP214_AutoDesignPresentedItemSelect::CaseNum, "Recognizes a AutoDesignPresentedItemSelect Kind Entity that is : 1 -> ProductDefinition, 2 -> ProductDefinitionRelationship, 3 -> ProductDefinitionShape 4 -> RepresentationRelationship 5 -> ShapeAspect 6 -> DocumentRelationship, 0 else", py::arg("ent"));
cls_StepAP214_AutoDesignPresentedItemSelect.def("ProductDefinitionRelationship", (opencascade::handle<StepBasic_ProductDefinitionRelationship> (StepAP214_AutoDesignPresentedItemSelect::*)() const) &StepAP214_AutoDesignPresentedItemSelect::ProductDefinitionRelationship, "returns Value as a ProductDefinitionRelationship (Null if another type)");
cls_StepAP214_AutoDesignPresentedItemSelect.def("ProductDefinition", (opencascade::handle<StepBasic_ProductDefinition> (StepAP214_AutoDesignPresentedItemSelect::*)() const) &StepAP214_AutoDesignPresentedItemSelect::ProductDefinition, "returns Value as a ProductDefinition (Null if another type)");
cls_StepAP214_AutoDesignPresentedItemSelect.def("ProductDefinitionShape", (opencascade::handle<StepRepr_ProductDefinitionShape> (StepAP214_AutoDesignPresentedItemSelect::*)() const) &StepAP214_AutoDesignPresentedItemSelect::ProductDefinitionShape, "returns Value as a ProductDefinitionShape (Null if another type)");
cls_StepAP214_AutoDesignPresentedItemSelect.def("RepresentationRelationship", (opencascade::handle<StepRepr_RepresentationRelationship> (StepAP214_AutoDesignPresentedItemSelect::*)() const) &StepAP214_AutoDesignPresentedItemSelect::RepresentationRelationship, "returns Value as a RepresentationRelationship (Null if another type)");
cls_StepAP214_AutoDesignPresentedItemSelect.def("ShapeAspect", (opencascade::handle<StepRepr_ShapeAspect> (StepAP214_AutoDesignPresentedItemSelect::*)() const) &StepAP214_AutoDesignPresentedItemSelect::ShapeAspect, "returns Value as a ShapeAspect (Null if another type)");
cls_StepAP214_AutoDesignPresentedItemSelect.def("DocumentRelationship", (opencascade::handle<StepBasic_DocumentRelationship> (StepAP214_AutoDesignPresentedItemSelect::*)() const) &StepAP214_AutoDesignPresentedItemSelect::DocumentRelationship, "returns Value as a DocumentRelationship (Null if another type)");

// Enums

}