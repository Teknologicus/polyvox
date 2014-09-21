/*******************************************************************************
Copyright (c) 2005-2009 David Williams

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution. 	
*******************************************************************************/

#ifndef __PolyVox_BaseVolume_H__
#define __PolyVox_BaseVolume_H__

#include "PolyVoxCore/Region.h"
#include "PolyVoxCore/Vector.h"

#include <limits>

namespace PolyVox
{
	/// The BaseVolume class provides common functionality and an interface for other volume classes to implement. You should not try to create an instance of this
	/// class directly. Instead you should use RawVolume or PagedVolume.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// More details to come...
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	namespace WrapModes
	{
		enum WrapMode
		{
			Validate = 0,
			Clamp = 1,
			Border = 2,
			AssumeValid = 3
		};
	}
	typedef WrapModes::WrapMode WrapMode;

	// Required for a trick to implement specialization of template member
	// functions in template classes. See http://stackoverflow.com/a/4951057
	template <WrapMode W> struct WrapModeType{};

	template <typename _VoxelType>
	class BaseVolume
	{
	public:
		typedef _VoxelType VoxelType;

		#ifndef SWIG
		template <typename DerivedVolumeType>
		class Sampler
		{
		public:
			Sampler(DerivedVolumeType* volume);
			~Sampler();

			Vector3DInt32 getPosition(void) const;
			inline VoxelType getVoxel(void) const;	

			bool isCurrentPositionValid(void) const;

			void setPosition(const Vector3DInt32& v3dNewPos);
			void setPosition(int32_t xPos, int32_t yPos, int32_t zPos);
			inline bool setVoxel(VoxelType tValue);
			void setWrapMode(WrapMode eWrapMode, VoxelType tBorder = VoxelType());

			void movePositiveX(void);
			void movePositiveY(void);
			void movePositiveZ(void);

			void moveNegativeX(void);
			void moveNegativeY(void);
			void moveNegativeZ(void);

			inline VoxelType peekVoxel1nx1ny1nz(void) const;
			inline VoxelType peekVoxel1nx1ny0pz(void) const;
			inline VoxelType peekVoxel1nx1ny1pz(void) const;
			inline VoxelType peekVoxel1nx0py1nz(void) const;
			inline VoxelType peekVoxel1nx0py0pz(void) const;
			inline VoxelType peekVoxel1nx0py1pz(void) const;
			inline VoxelType peekVoxel1nx1py1nz(void) const;
			inline VoxelType peekVoxel1nx1py0pz(void) const;
			inline VoxelType peekVoxel1nx1py1pz(void) const;

			inline VoxelType peekVoxel0px1ny1nz(void) const;
			inline VoxelType peekVoxel0px1ny0pz(void) const;
			inline VoxelType peekVoxel0px1ny1pz(void) const;
			inline VoxelType peekVoxel0px0py1nz(void) const;
			inline VoxelType peekVoxel0px0py0pz(void) const;
			inline VoxelType peekVoxel0px0py1pz(void) const;
			inline VoxelType peekVoxel0px1py1nz(void) const;
			inline VoxelType peekVoxel0px1py0pz(void) const;
			inline VoxelType peekVoxel0px1py1pz(void) const;

			inline VoxelType peekVoxel1px1ny1nz(void) const;
			inline VoxelType peekVoxel1px1ny0pz(void) const;
			inline VoxelType peekVoxel1px1ny1pz(void) const;
			inline VoxelType peekVoxel1px0py1nz(void) const;
			inline VoxelType peekVoxel1px0py0pz(void) const;
			inline VoxelType peekVoxel1px0py1pz(void) const;
			inline VoxelType peekVoxel1px1py1nz(void) const;
			inline VoxelType peekVoxel1px1py0pz(void) const;
			inline VoxelType peekVoxel1px1py1pz(void) const;

		protected:
			VoxelType getVoxelImpl(int32_t uXPos, int32_t uYPos, int32_t uZPos) const;

			DerivedVolumeType* mVolume;

			//The current position in the volume
			int32_t mXPosInVolume;
			int32_t mYPosInVolume;
			int32_t mZPosInVolume;

			WrapMode m_eWrapMode;
			VoxelType m_tBorder;

			//Whether the current position is inside the volume
			//FIXME - Replace these with flags
			bool m_bIsCurrentPositionValidInX;
			bool m_bIsCurrentPositionValidInY;
			bool m_bIsCurrentPositionValidInZ;
		};
		#endif

	public:
		/// Gets the value used for voxels which are outside the volume
		VoxelType getBorderValue(void) const;
		/// Gets a Region representing the extents of the Volume.
		const Region& getEnclosingRegion(void) const;
		/// Gets the width of the volume in voxels.
		int32_t getWidth(void) const;
		/// Gets the height of the volume in voxels.
		int32_t getHeight(void) const;
		/// Gets the depth of the volume in voxels.
		int32_t getDepth(void) const;
		/// Gets the length of the longest side in voxels
		int32_t getLongestSideLength(void) const;
		/// Gets the length of the shortest side in voxels
		int32_t getShortestSideLength(void) const;
		/// Gets the length of the diagonal in voxels
		float getDiagonalLength(void) const;
		
		/// Gets a voxel at the position given by <tt>x,y,z</tt> coordinates
		template <WrapMode eWrapMode>
		VoxelType getVoxel(int32_t uXPos, int32_t uYPos, int32_t uZPos, VoxelType tBorder = VoxelType()) const;
		/// Gets a voxel at the position given by a 3D vector
		template <WrapMode eWrapMode>
		VoxelType getVoxel(const Vector3DInt32& v3dPos, VoxelType tBorder = VoxelType()) const;

		/// Gets a voxel at the position given by <tt>x,y,z</tt> coordinates
		VoxelType getVoxel(int32_t uXPos, int32_t uYPos, int32_t uZPos, WrapMode eWrapMode = WrapModes::Validate, VoxelType tBorder = VoxelType()) const;
		/// Gets a voxel at the position given by a 3D vector
		VoxelType getVoxel(const Vector3DInt32& v3dPos, WrapMode eWrapMode = WrapModes::Validate, VoxelType tBorder = VoxelType()) const;
		
		/// Gets a voxel at the position given by <tt>x,y,z</tt> coordinates
		POLYVOX_DEPRECATED VoxelType getVoxelAt(int32_t uXPos, int32_t uYPos, int32_t uZPos) const;
		/// Gets a voxel at the position given by a 3D vector
		POLYVOX_DEPRECATED VoxelType getVoxelAt(const Vector3DInt32& v3dPos) const;

		/// Sets the value used for voxels which are outside the volume
		void setBorderValue(const VoxelType& tBorder);
		/// Sets the voxel at the position given by <tt>x,y,z</tt> coordinates
		void setVoxel(int32_t uXPos, int32_t uYPos, int32_t uZPos, VoxelType tValue, WrapMode eWrapMode = WrapModes::Validate);
		/// Sets the voxel at the position given by a 3D vector
		void setVoxel(const Vector3DInt32& v3dPos, VoxelType tValue, WrapMode eWrapMode = WrapModes::Validate);
		/// Sets the voxel at the position given by <tt>x,y,z</tt> coordinates
		bool setVoxelAt(int32_t uXPos, int32_t uYPos, int32_t uZPos, VoxelType tValue);
		/// Sets the voxel at the position given by a 3D vector
		bool setVoxelAt(const Vector3DInt32& v3dPos, VoxelType tValue);

		/// Calculates approximatly how many bytes of memory the volume is currently using.
		uint32_t calculateSizeInBytes(void);

	protected:	
		/// Constructor for creating a fixed size volume.
		BaseVolume(const Region& regValid);

		/// Copy constructor
		BaseVolume(const BaseVolume& rhs);

		/// Destructor
		~BaseVolume();

		/// Assignment operator
		BaseVolume& operator=(const BaseVolume& rhs);

		//The size of the volume
		Region m_regValidRegion;

		//Some useful sizes
		int32_t m_uLongestSideLength;
		int32_t m_uShortestSideLength;
		float m_fDiagonalLength;

		//The border value
		VoxelType m_tBorderValue;
	};
}

#include "PolyVoxCore/BaseVolume.inl"
#include "PolyVoxCore/BaseVolumeSampler.inl"

#endif //__PolyVox_BaseVolume_H__
