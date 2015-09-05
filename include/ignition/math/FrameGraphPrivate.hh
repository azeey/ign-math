/*
 * Copyright (C) 2015 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef _IGNITION_FRAMEGRAPH_PRIVATE_HH_
#define _IGNITION_FRAMEGRAPH_PRIVATE_HH_

#include <mutex>
#include <array>
#include <map>
#include <ignition/math/Pose3.hh>

#include <ignition/math/FrameGraph.hh>

namespace ignition
{
  namespace math
  {
    class PathPrivate
    {
      public: PathPrivate(const std::string &_path);

      /// \brief Removes the last element of the path.
      /// if the path only has one element, nothing is removed.
      public: void PopLeaf();
      public: const std::vector<std::string> & Elems() const;
      public: const std::string &Root() const;
      public: const std::string &Leaf() const;
      public: const std::string &Path() const;
      public: bool IsFull() const;
      private: void Dump() const;
      private: std::string path;
      private: std::vector<std::string> pathElems;
    };
/*
    class FramePrivate
    {
      public: FramePrivate(const std::string &_name,
                        const Pose3d& _pose,
                        const FramePrivate*_parentFrame);
      public: std::string name;
      public: Pose3d pose;
      // this is a direct pointer to the parent
      // frame, that speeds up lookup.
      public: const FramePrivate *parentFrame;

      public: std::map<std::string, const FramePrivate*> children;
    };
*/
    /// \internal
    class RelativePosePrivate
    {
      public: RelativePosePrivate();
      public: ~RelativePosePrivate() = default;
      public: mutable std::mutex *mutex;
      public: std::vector<const FramePrivate *> up;
      public: std::vector<const FramePrivate *> down;
    };

    /// \internal
    /// \brief Private data for the Frustum class
    class FrameGraphPrivate
    {
      /// \brief Constructor
      public: FrameGraphPrivate();

      /// \brief destructor
      public: ~FrameGraphPrivate();

      /// \brief
      public: const FramePrivate* FrameFromAbsolutePath(
                                               const PathPrivate& _path) const;

      public: FramePrivate* FrameFromAbsolutePath(const PathPrivate& _path);

      public: const FramePrivate* FrameFromRelativePath(const FramePrivate *_frame,
                                           const  PathPrivate& _relPath) const;

      public: FramePrivate world;
      public: mutable std::mutex mutex;
    };
  }
}

#endif