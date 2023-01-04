#include "functions.h"

cv::Mat to_cvmat(ARGB* image, const int& width, const int& height, const bool& monochrome = false) noexcept {

	if (monochrome) {
	} else {
		cv::Mat rgb = cv::Mat::zeros(width, height, CV_8UC3);
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x) {
				rgb.at<cv::Vec3b>(x, y)[0] = uchar(image[x + y * width].b);
				rgb.at<cv::Vec3b>(x, y)[1] = uchar(image[x + y * width].g);
				rgb.at<cv::Vec3b>(x, y)[2] = uchar(image[x + y * width].r);
			}
		return rgb;
	}
}

void assign_cvmat(ARGB* image, const int& width, const int& height, cv::Mat mat) {
	
	switch (mat.type()) {
	case CV_8UC3:
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x) {
				image[x + y * width].b = std::byte(mat.at<cv::Vec3b>(x, y)[0]);
				image[x + y * width].g = std::byte(mat.at<cv::Vec3b>(x, y)[1]);
				image[x + y * width].r = std::byte(mat.at<cv::Vec3b>(x, y)[2]);
			}
		return;
	case CV_8UC1:
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x) {
				image[x + y * width].b = std::byte(mat.at<cv::Vec<uchar, 1>>(x, y)[0]);
				image[x + y * width].g = std::byte(mat.at<cv::Vec<uchar, 1>>(x, y)[0]);
				image[x + y * width].r = std::byte(mat.at<cv::Vec<uchar, 1>>(x, y)[0]);
			}
		return;
	default:
		return;
	}
}

ErrorMsg opencv_binalization(ARGB* image, const int& width, const int& height, const RGB& dark, const RGB& blight, const int& mode) {		
	cv::Mat src = to_cvmat(image, width, height), dest(width, height, CV_8UC3);
	cv::threshold(src, dest, 128, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
	assign_cvmat(image, width, height, src);
	return "";
}