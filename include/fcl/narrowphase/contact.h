/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2011-2014, Willow Garage, Inc.
 *  Copyright (c) 2014-2016, Open Source Robotics Foundation
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Open Source Robotics Foundation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/** @author Jia Pan */

#ifndef FCL_CONTACT_H
#define FCL_CONTACT_H

#include "fcl/narrowphase/collision_object.h"

namespace fcl {

/// @brief Contact information returned by collision
template <typename S>
struct Contact {
  /// @brief collision object 1
  const CollisionGeometry<S>* o1;

  /// @brief collision object 2
  const CollisionGeometry<S>* o2;

  /// @brief contact primitive in object 1
  /// if object 1 is mesh or point cloud, it is the triangle or point id
  /// if object 1 is geometry shape, it is NONE (-1),
  /// if object 1 is octree, it is the query cell id (see
  ///                OcTree::getNodeByQueryCellId)
  intptr_t b1;

  /// @brief contact primitive in object 2
  /// if object 2 is mesh or point cloud, it is the triangle or point id
  /// if object 2 is geometry shape, it is NONE (-1),
  /// if object 2 is octree, it is the query cell id (see
  ///                OcTree::getNodeByQueryCellId)
  intptr_t b2;

  /// @brief Contact information, using the same convection as ContactPoint
  ///        Thus please refer to the document of ContactPoint
  Vector3<S> normal;
  Vector3<S> pos;
  S penetration_depth;
  Vector3<S> point_on_shape1() const;
  Vector3<S> point_on_shape2() const;
  Vector3<S> shape2_escape_movement(
      S penetration_depth_scaled_by = S(1.0)) const;
  Vector3<S> shape1_escape_movement(
      S penetration_depth_scaled_by = S(1.0)) const;

  /// For octree/heightmap collision
  /// If none of o1 and o2 is octree/heightmap, then ignore these results below
  /// If o1 and o2 are all octree/heightmap, then the name are clear
  /// If o1 OR o2 are octree/heightmap, then the bounding box is written to the
  /// corresponded objects (o1_bv or o2_bv).
  AABB<S> o1_bv;
  AABB<S> o2_bv;

  /// @brief invalid contact primitive information
  static constexpr int NONE = -1;

  Contact();
  Contact(const CollisionGeometry<S>* o1_, const CollisionGeometry<S>* o2_,
          int b1_, int b2_);
  Contact(const CollisionGeometry<S>* o1_, const CollisionGeometry<S>* o2_,
          int b1_, int b2_, const Vector3<S>& pos_, const Vector3<S>& normal_,
          S depth_);
  bool operator<(const Contact& other) const;
};

using Contactf = Contact<float>;
using Contactd = Contact<double>;

}  // namespace fcl

#include "fcl/narrowphase/contact-inl.h"

#endif
