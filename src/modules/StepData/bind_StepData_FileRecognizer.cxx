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
#include <Standard_Transient.hxx>
#include <Standard_TypeDef.hxx>
#include <TCollection_AsciiString.hxx>
#include <Standard_Handle.hxx>
#include <StepData_FileRecognizer.hxx>
#include <Standard_Type.hxx>

void bind_StepData_FileRecognizer(py::module &mod){

py::class_<StepData_FileRecognizer, opencascade::handle<StepData_FileRecognizer>, Standard_Transient> cls_StepData_FileRecognizer(mod, "StepData_FileRecognizer", "None");

// Fields

// Methods
cls_StepData_FileRecognizer.def("Evaluate", (Standard_Boolean (StepData_FileRecognizer::*)(const TCollection_AsciiString &, opencascade::handle<Standard_Transient> &)) &StepData_FileRecognizer::Evaluate, "Evaluates if recognition has a result, returns it if yes In case of success, Returns True and puts result in 'res' In case of Failure, simply Returns False Works by calling deferred method Eval, and in case of failure, looks for Added Recognizers to work", py::arg("akey"), py::arg("res"));
cls_StepData_FileRecognizer.def("Result", (opencascade::handle<Standard_Transient> (StepData_FileRecognizer::*)() const) &StepData_FileRecognizer::Result, "Returns result of last recognition (call of Evaluate)");
cls_StepData_FileRecognizer.def("Add", (void (StepData_FileRecognizer::*)(const opencascade::handle<StepData_FileRecognizer> &)) &StepData_FileRecognizer::Add, "Adds a new Recognizer to the Compound, at the end Several calls to Add work by adding in the order of calls : Hence, when Eval has failed to recognize, Evaluate will call Evaluate from the first added Recognizer if there is one, and to the second if there is still no result, and so on", py::arg("reco"));
cls_StepData_FileRecognizer.def_static("get_type_name_", (const char * (*)()) &StepData_FileRecognizer::get_type_name, "None");
cls_StepData_FileRecognizer.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_FileRecognizer::get_type_descriptor, "None");
cls_StepData_FileRecognizer.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_FileRecognizer::*)() const) &StepData_FileRecognizer::DynamicType, "None");

// Enums

}