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
#include <Standard_Handle.hxx>
#include <Standard_Transient.hxx>
#include <Standard_GUID.hxx>
#include <Standard_TypeDef.hxx>
#include <Plugin.hxx>

void bind_Plugin(py::module &mod){

py::class_<Plugin, std::unique_ptr<Plugin, Deleter<Plugin>>> cls_Plugin(mod, "Plugin", "None");

// Constructors

// Fields

// Methods
cls_Plugin.def_static("Load_", [](const Standard_GUID & a0) -> opencascade::handle<Standard_Transient> { return Plugin::Load(a0); });
cls_Plugin.def_static("Load_", (opencascade::handle<Standard_Transient> (*)(const Standard_GUID &, const Standard_Boolean)) &Plugin::Load, "None", py::arg("aGUID"), py::arg("theVerbose"));

// Enums

}