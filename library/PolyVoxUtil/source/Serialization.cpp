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

#include "Serialization.h"

#include "Volume.h"
#include "VolumeSampler.h"
#include "PolyVoxImpl/Utility.h"

using namespace std;

namespace PolyVox
{
	//Note: we don't do much error handling in here - exceptions will simply be propergated up to the caller.
	//FIXME - think about pointer ownership issues. Or could return volume by value if the copy constructor is shallow
	shared_ptr< Volume<uint8_t> > loadVolumeRaw(istream& stream, VolumeSerializationProgressListener* progressListener)
	{
		//Read volume dimensions
		uint8_t volumeWidthPower = 0;
		uint8_t volumeHeightPower = 0;
		uint8_t volumeDepthPower = 0;
		stream.read(reinterpret_cast<char*>(&volumeWidthPower), sizeof(volumeWidthPower));
		stream.read(reinterpret_cast<char*>(&volumeHeightPower), sizeof(volumeHeightPower));
		stream.read(reinterpret_cast<char*>(&volumeDepthPower), sizeof(volumeDepthPower));

		uint16_t volumeWidth = 0x0001 << volumeWidthPower;
		uint16_t volumeHeight = 0x0001 << volumeHeightPower;
		uint16_t volumeDepth = 0x0001 << volumeDepthPower;

		//FIXME - need to support non cubic volumes
		shared_ptr< Volume<uint8_t> > volume(new Volume<uint8_t>(volumeWidth, volumeHeight, volumeDepth));

		//Read data
		for(uint16_t z = 0; z < volumeDepth; ++z)
		{
			//Update progress once per slice.
			if(progressListener)
			{
				float fProgress = static_cast<float>(z) / static_cast<float>(volumeDepth);
				progressListener->onProgressUpdated(fProgress);
			}

			for(uint16_t y = 0; y < volumeHeight; ++y)
			{
				for(uint16_t x = 0; x < volumeWidth; ++x)
				{
					uint8_t value = 0;
					stream.read(reinterpret_cast<char*>(&value), sizeof(value));

					volume->setVoxelAt(x,y,z,value);
				}
			}
		}

		//Finished
		if(progressListener)
		{
			progressListener->onProgressUpdated(1.0f);
		}

		return volume;
	}

	void saveVolumeRaw(std::ostream& stream, Volume<uint8_t>& volume, VolumeSerializationProgressListener* progressListener)
	{
		//Write volume dimensions
		uint16_t volumeWidth = volume.getWidth();
		uint16_t volumeHeight = volume.getHeight();
		uint16_t volumeDepth  = volume.getDepth();

		uint8_t volumeWidthPower = logBase2(volumeWidth);
		uint8_t volumeHeightPower = logBase2(volumeHeight);
		uint8_t volumeDepthPower = logBase2(volumeDepth);

		stream.write(reinterpret_cast<char*>(&volumeWidthPower), sizeof(volumeWidthPower));
		stream.write(reinterpret_cast<char*>(&volumeHeightPower), sizeof(volumeHeightPower));
		stream.write(reinterpret_cast<char*>(&volumeDepthPower), sizeof(volumeDepthPower));

		//Write data
		VolumeSampler<uint8_t> volIter(&volume);
		for(uint16_t z = 0; z < volumeDepth; ++z)
		{
			//Update progress once per slice.
			if(progressListener)
			{
				float fProgress = static_cast<float>(z) / static_cast<float>(volumeDepth);
				progressListener->onProgressUpdated(fProgress);
			}

			for(uint16_t y = 0; y < volumeHeight; ++y)
			{
				for(uint16_t x = 0; x < volumeWidth; ++x)
				{
					volIter.setPosition(x,y,z);
					uint8_t value = volIter.getVoxel();
					stream.write(reinterpret_cast<char*>(&value), sizeof(value));
				}
			}
		}

		//Finished
		if(progressListener)
		{
			progressListener->onProgressUpdated(1.0f);
		}
	}

	//Note: we don't do much error handling in here - exceptions will simply be propergated up to the caller.
	//FIXME - think about pointer ownership issues. Or could return volume by value if the copy constructor is shallow
	shared_ptr< Volume<uint8_t> > loadVolumeRle(istream& stream, VolumeSerializationProgressListener* progressListener)
	{
		//Read volume dimensions
		uint8_t volumeWidthPower = 0;
		uint8_t volumeHeightPower = 0;
		uint8_t volumeDepthPower = 0;
		stream.read(reinterpret_cast<char*>(&volumeWidthPower), sizeof(volumeWidthPower));
		stream.read(reinterpret_cast<char*>(&volumeHeightPower), sizeof(volumeHeightPower));
		stream.read(reinterpret_cast<char*>(&volumeDepthPower), sizeof(volumeDepthPower));

		uint16_t volumeWidth = 0x0001 << volumeWidthPower;
		uint16_t volumeHeight = 0x0001 << volumeHeightPower;
		uint16_t volumeDepth = 0x0001 << volumeDepthPower;

		//FIXME - need to support non cubic volumes
		shared_ptr< Volume<uint8_t> > volume(new Volume<uint8_t>(volumeWidth, volumeHeight, volumeDepth));

		//Read data
		bool firstTime = true;
		uint32_t runLength = 0;
		uint8_t value = 0;
		stream.read(reinterpret_cast<char*>(&value), sizeof(value));
		stream.read(reinterpret_cast<char*>(&runLength), sizeof(runLength));
		for(uint16_t z = 0; z < volumeDepth; ++z)
		{
			//Update progress once per slice.
			if(progressListener)
			{
				float fProgress = static_cast<float>(z) / static_cast<float>(volumeDepth);
				progressListener->onProgressUpdated(fProgress);
			}

			for(uint16_t y = 0; y < volumeHeight; ++y)
			{
				for(uint16_t x = 0; x < volumeWidth; ++x)
				{	
					if(runLength != 0)
					{
						volume->setVoxelAt(x,y,z,value);
						runLength--;
					}
					else
					{
						stream.read(reinterpret_cast<char*>(&value), sizeof(value));
						stream.read(reinterpret_cast<char*>(&runLength), sizeof(runLength));

						volume->setVoxelAt(x,y,z,value);
						runLength--;
					}
				}
			}			
		}

		//Finished
		if(progressListener)
		{
			progressListener->onProgressUpdated(1.0f);
		}

		return volume;
	}

	void saveVolumeRle(std::ostream& stream, Volume<uint8_t>& volume, VolumeSerializationProgressListener* progressListener)
	{
		//Write volume dimensions
		uint16_t volumeWidth = volume.getWidth();
		uint16_t volumeHeight = volume.getHeight();
		uint16_t volumeDepth  = volume.getDepth();

		uint8_t volumeWidthPower = logBase2(volumeWidth);
		uint8_t volumeHeightPower = logBase2(volumeHeight);
		uint8_t volumeDepthPower = logBase2(volumeDepth);

		stream.write(reinterpret_cast<char*>(&volumeWidthPower), sizeof(volumeWidthPower));
		stream.write(reinterpret_cast<char*>(&volumeHeightPower), sizeof(volumeHeightPower));
		stream.write(reinterpret_cast<char*>(&volumeDepthPower), sizeof(volumeDepthPower));

		//Write data
		VolumeSampler<uint8_t> volIter(&volume);
		uint8_t current = 0;
		uint32_t runLength = 0;
		bool firstTime = true;
		for(uint16_t z = 0; z < volumeDepth; ++z)
		{
			//Update progress once per slice.
			if(progressListener)
			{
				float fProgress = static_cast<float>(z) / static_cast<float>(volumeDepth);
				progressListener->onProgressUpdated(fProgress);
			}

			for(uint16_t y = 0; y < volumeHeight; ++y)
			{
				for(uint16_t x = 0; x < volumeWidth; ++x)
				{		
					volIter.setPosition(x,y,z);
					uint8_t value = volIter.getVoxel();
					if(firstTime)
					{
						current = value;
						runLength = 1;
						firstTime = false;
					}
					else
					{
						if(value == current)
						{
							runLength++;
						}
						else
						{
							stream.write(reinterpret_cast<char*>(&current), sizeof(current));
							stream.write(reinterpret_cast<char*>(&runLength), sizeof(runLength));
							current = value;
							runLength = 1;
						}
					}					
				}
			}
		}
		stream.write(reinterpret_cast<char*>(&current), sizeof(current));
		stream.write(reinterpret_cast<char*>(&runLength), sizeof(runLength));

		//Finished
		if(progressListener)
		{
			progressListener->onProgressUpdated(1.0f);
		}
	}
}