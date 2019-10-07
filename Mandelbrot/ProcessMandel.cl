__kernel void (const double* graphPoints, uint8* pixels, const uint8* colorMap, const unsigned colorMapSize, const unsigned maxIterations)
{
	size_t id = (get_global_id(0) * get_global_id(1)) + get_global_id(1);
	size_t pId = // need a way to get pixel id
	double real = graphPoints[id];
	double realResult = real;
	double realTemp = 0.;
	double imaginary = graphPoints[id + 1];
	double imaginaryResult = imaginary;
	double mag = 0.;
	
	unsigned iterations = 0;
	while (iterations < maxIterations)
	{
		realTemp = (realResult * realResult) + (imaginaryResult * imaginaryResult * -1) + real;
		imaginaryResult = (2*realResult*imaginaryResult) + imaginary;
		realResult = realTemp;
		
		mag = sqrt(realResult*realResult + imaginaryResult*imaginaryResult);
		
		if (mag > 2)
		{
			float hue = (iterations - log2(log2(mag) + 4.0)) / maxIterations;
			if (hue > 1)
				hue = 1;
			unsigned index = unsigned(1 + unsigned((hue) * colorMapSize) % colorMapSize);
			pixels[pId] = colorMap[index + 0];
			pixels[pId + 1] = colorMap[index + 1];
			pixels[pId + 2] = colorMap[index + 2];
			pixels[pId + 3] = colorMap[index + 3];
			break;
		}
		++iterations;
	}
	
	if (iterations == maxIterations)
	{
		pixels[pId] = colorMap[0];
		pixels[pId + 1] = colorMap[1];
		pixels[pId + 2] = colorMap[2];
		pixels[pId + 3] = colorMap[3];
	}

}