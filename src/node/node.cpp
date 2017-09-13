//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty ofMERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the
// Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor
// Boston, MA  02110-1301 USA
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Sep 11, 2017
//
#include <stdexcept>
#include <h5cpp/node/node.hpp>

namespace hdf5 {
namespace node {

Node::Node(ObjectHandle &&handle,const Path &path):
    handle_(std::move(handle)),
    path_(path)
{}

Node::~Node()
{}

Path Node::path() const
{
  return path_;
}

Type Node::type() const
{
  H5O_info_t info;
  if(H5Oget_info(static_cast<hid_t>(*this),&info)<0)
  {
    throw std::runtime_error("Error retrieving type information for this node!");
  }

  return static_cast<Type>(info.type);
}

bool Node::is_valid() const
{
  return handle_.is_valid();
}

ObjectId Node::id() const
{
  return ObjectId(static_cast<hid_t>(*this));
}

} // namespace node
} // namespace hdf5