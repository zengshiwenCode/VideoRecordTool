#include "stdafx.h"
#include "config.h"
#include <fstream>
#include "jsoncpp/json.h"
#include <filesystem>
#include "duilib.h"

namespace bfs = std::experimental::filesystem;


namespace {

auto keyVid = "vid";
auto keyAid = "aid";

auto secVideo = "video";
	auto keyWidth = "width";
	auto keyHeight = "height";
	auto keyRoot = "root";
	auto keyType = "type";
	auto keyTime = "rectime";

	auto keyValid = "valid";
	auto keyValue = "value";

	auto segProcamp = "procamp";
		auto keyBacklight = "backlight";
		auto keyBrightness = "brightness";
		auto keyContrast = "contrast";
		auto keyGain = "gain";
		auto keyGamma = "gamma";
		auto keyHue = "hue";
		auto keySaturation = "saturation";
		auto keySharpness = "sharpness";
		auto keyWhiteBalance = "white_balance";

	auto segCamera = "camera_settins";
		auto keyExposure = "exposure";
		auto keyFocus = "focus";
		auto keyIris = "iris";
		auto keyPan = "pan";
		auto keyRoll = "roll";
		auto keyTilt = "tilt";
		auto keyZoom = "zoom";

auto secSerial = "serial";
	auto keyPort = "port";
	auto keyBaudrate = "baudrate";

auto keyLang = "language";


}

config::config()
{
	cfg_file_ = get_exe_path_a() + "\\cfg.json";
	if (!load()) {
		init();
		save();
	}
}

bool config::load()
{
	std::ifstream in(cfg_file_);
	if (!in) { return false; }

	Json::Value value;
	Json::Reader reader;
	if (reader.parse(in, value)) {
		_aidx = value[keyAid].asInt();
		_vidx = value[keyVid].asInt();

		_video_w = value[secVideo][keyWidth].asInt();
		_video_h = value[secVideo][keyHeight].asInt();
		_root = value[secVideo][keyRoot].asString();
		if (_root.empty() || !std::experimental::filesystem::is_directory(_root) || !std::experimental::filesystem::exists(_root)) {
			init_root();
		}
		_vtype = value[secVideo][keyType].asString();
		_max_rec_minutes = value[secVideo][keyTime].asInt();

		/*_procamp.backlight.val_ = value[secVideo][segProcamp][keyBacklight][keyValue].asInt();
		_procamp.brightness.val_ = value[secVideo][segProcamp][keyBrightness][keyValue].asInt();
		_procamp.contrast.val_ = value[secVideo][segProcamp][keyContrast][keyValue].asInt();
		_procamp.gain.val_ = value[secVideo][segProcamp][keyGain][keyValue].asInt();
		_procamp.gamma.val_ = value[secVideo][segProcamp][keyGamma][keyValue].asInt();
		_procamp.hue.val_ = value[secVideo][segProcamp][keyHue][keyValue].asInt();
		_procamp.saturation.val_ = value[secVideo][segProcamp][keySaturation][keyValue].asInt();
		_procamp.sharpness.val_ = value[secVideo][segProcamp][keySharpness][keyValue].asInt();
		_procamp.white_balance.val_ = value[secVideo][segProcamp][keyWhiteBalance][keyValue].asInt();

		_procamp.backlight.valid_ = value[secVideo][segProcamp][keyBacklight][keyValid].asInt();
		_procamp.brightness.valid_ = value[secVideo][segProcamp][keyBrightness][keyValid].asInt();
		_procamp.contrast.valid_ = value[secVideo][segProcamp][keyContrast][keyValid].asInt();
		_procamp.gain.valid_ = value[secVideo][segProcamp][keyGain][keyValid].asInt();
		_procamp.gamma.valid_ = value[secVideo][segProcamp][keyGamma][keyValid].asInt();
		_procamp.hue.valid_ = value[secVideo][segProcamp][keyHue][keyValid].asInt();
		_procamp.saturation.valid_ = value[secVideo][segProcamp][keySaturation][keyValid].asInt();
		_procamp.sharpness.valid_ = value[secVideo][segProcamp][keySharpness][keyValid].asInt();
		_procamp.white_balance.valid_ = value[secVideo][segProcamp][keyWhiteBalance][keyValid].asInt();

		_camera.exposure.val_ = value[secVideo][segCamera][keyExposure][keyValue].asInt();
		_camera.focus.val_ = value[secVideo][segCamera][keyFocus][keyValue].asInt();
		_camera.iris.val_ = value[secVideo][segCamera][keyIris][keyValue].asInt();
		_camera.pan.val_ = value[secVideo][segCamera][keyPan][keyValue].asInt();
		_camera.roll.val_ = value[secVideo][segCamera][keyRoll][keyValue].asInt();
		_camera.tilt.val_ = value[secVideo][segCamera][keyTilt][keyValue].asInt();
		_camera.zoom.val_ = value[secVideo][segCamera][keyZoom][keyValue].asInt();

		_camera.exposure.valid_ = value[secVideo][segCamera][keyExposure][keyValid].asInt();
		_camera.focus.valid_ = value[secVideo][segCamera][keyFocus][keyValid].asInt();
		_camera.iris.valid_ = value[secVideo][segCamera][keyIris][keyValid].asInt();
		_camera.pan.valid_ = value[secVideo][segCamera][keyPan][keyValid].asInt();
		_camera.roll.valid_ = value[secVideo][segCamera][keyRoll][keyValid].asInt();
		_camera.tilt.valid_ = value[secVideo][segCamera][keyTilt][keyValid].asInt();
		_camera.zoom.valid_ = value[secVideo][segCamera][keyZoom][keyValid].asInt();*/


		_port = value[secSerial][keyPort].asString();
		_baudrate = value[secSerial][keyBaudrate].asInt();

		_lang = value[keyLang].asString();
		if (_lang != "en") {
			_lang = "zh_CN";
		}

		return true;
	}

	return false;
}

bool config::save()
{
	std::ofstream out(cfg_file_);
	if (!out) { return false; }

	Json::Value value;
	value[keyAid] = _aidx;
	value[keyVid] = _vidx;

	value[secVideo][keyWidth] = _video_w;
	value[secVideo][keyHeight] = _video_h;
	value[secVideo][keyRoot] = _root;
	value[secVideo][keyType] = _vtype;
	value[secVideo][keyTime] = _max_rec_minutes;

	/*value[secVideo][segProcamp][keyBacklight][keyValid] = _procamp.backlight.valid_;
	value[secVideo][segProcamp][keyBrightness][keyValid] = _procamp.brightness.valid_;
	value[secVideo][segProcamp][keyContrast][keyValid] = _procamp.contrast.valid_;
	value[secVideo][segProcamp][keyGain][keyValid] = _procamp.gain.valid_;
	value[secVideo][segProcamp][keyGamma][keyValid] = _procamp.gamma.valid_;
	value[secVideo][segProcamp][keyHue][keyValid] = _procamp.hue.valid_;
	value[secVideo][segProcamp][keySaturation][keyValid] = _procamp.saturation.valid_;
	value[secVideo][segProcamp][keySharpness][keyValid] = _procamp.sharpness.valid_;
	value[secVideo][segProcamp][keyWhiteBalance][keyValid] = _procamp.white_balance.valid_;

	value[secVideo][segProcamp][keyBacklight][keyValue] = _procamp.backlight.val_;
	value[secVideo][segProcamp][keyBrightness][keyValue] = _procamp.brightness.val_;
	value[secVideo][segProcamp][keyContrast][keyValue] = _procamp.contrast.val_;
	value[secVideo][segProcamp][keyGain][keyValue] = _procamp.gain.val_;
	value[secVideo][segProcamp][keyGamma][keyValue] = _procamp.gamma.val_;
	value[secVideo][segProcamp][keyHue][keyValue] = _procamp.hue.val_;
	value[secVideo][segProcamp][keySaturation][keyValue] = _procamp.saturation.val_;
	value[secVideo][segProcamp][keySharpness][keyValue] = _procamp.sharpness.val_;
	value[secVideo][segProcamp][keyWhiteBalance][keyValue] = _procamp.white_balance.val_;

	value[secVideo][segCamera][keyExposure][keyValid] = _camera.exposure.valid_;
	value[secVideo][segCamera][keyFocus][keyValid] = _camera.focus.valid_;
	value[secVideo][segCamera][keyIris][keyValid] = _camera.iris.valid_;
	value[secVideo][segCamera][keyPan][keyValid] = _camera.pan.valid_;
	value[secVideo][segCamera][keyRoll][keyValid] = _camera.roll.valid_;
	value[secVideo][segCamera][keyTilt][keyValid] = _camera.tilt.valid_;
	value[secVideo][segCamera][keyZoom][keyValid] = _camera.zoom.valid_;

	value[secVideo][segCamera][keyExposure][keyValue] = _camera.exposure.val_;
	value[secVideo][segCamera][keyFocus][keyValue] = _camera.focus.val_;
	value[secVideo][segCamera][keyIris][keyValue] = _camera.iris.val_;
	value[secVideo][segCamera][keyPan][keyValue] = _camera.pan.val_;
	value[secVideo][segCamera][keyRoll][keyValue] = _camera.roll.val_;
	value[secVideo][segCamera][keyTilt][keyValue] = _camera.tilt.val_;
	value[secVideo][segCamera][keyZoom][keyValue] = _camera.zoom.val_;*/


	value[secSerial][keyPort] = _port;
	value[secSerial][keyBaudrate] = _baudrate;

	value[keyLang] = _lang;

	Json::StyledStreamWriter writer;
	writer.write(out, value);

	return true;
}

void config::init()
{
	_vidx = 0;
	_aidx = 0;

	// video
	_video_w = 640;
	_video_h = 480;
	init_root();

	// serial
	_port = "COM1";
	_baudrate = 9600;

	// language
	_lang = "zh_CN";
}

void config::init_root()
{
	_root = get_exe_path_a() + "\\" + VR_ROOT_FOLDER;
	CreateDirectoryA(_root.c_str(), nullptr);
	auto vpath = _root + "\\" + VR_VIDEO_FOLDER;
	CreateDirectoryA(vpath.c_str(), nullptr);
	auto cpath = _root + "\\" + VR_CAPTURE_FOLDER;
	CreateDirectoryA(cpath.c_str(), nullptr);
}

bool config::clear_root() const
{
	bool ok = true;
	std::error_code ec1, ec2, ec3;
	bfs::path capture(get_capture_path());
	bfs::remove_all(capture, ec1);
	bfs::path record(get_video_path());
	bfs::remove_all(record, ec2);
	bfs::path thumb(get_thumb_path());
	bfs::remove_all(thumb, ec3);
	if (ec1) {
		ok = false;
		JLOG_ERRO(ec1.message());
	}
	if (ec2) {
		ok = false;
		JLOG_ERRO(ec2.message());
	}
	if (ec3) {
		ok = false;
		JLOG_ERRO(ec3.message());
	}

	return ok;
}

std::string config::get_version() const
{
	return std::string("1.0.0.1");
}

std::string config::get_remainder_space() const
{
	auto path = bfs::canonical(_root);
	auto root = path.root_path();
	bfs::space_info si = bfs::space(root);
	si.available;

	auto format_space = [](uintmax_t bytes) {
		const int factor = 1024;
		uintmax_t kb = bytes / factor;
		uintmax_t mb = kb / factor;
		uintmax_t gb = mb / factor;

		std::string s;
		if (gb > 0) {
			return std::to_string(gb) + "G";
		} else {
			return std::to_string(mb) + "M";
		}
	};

	return format_space(si.available) + "/" + format_space(si.capacity);
}

std::string config::get_video_path() const
{
	auto p = _root + "\\" + VR_VIDEO_FOLDER;
	CreateDirectoryA(p.c_str(), nullptr);
	return p;
}

std::string config::get_capture_path() const
{
	auto p = _root + "\\" + VR_CAPTURE_FOLDER;
	CreateDirectoryA(p.c_str(), nullptr);
	return p;
}

std::string config::create_new_video_path() const
{
	auto s = now_to_string();
	s.erase(std::remove(s.begin(), s.end(), '-'), s.end());
	s.erase(std::remove(s.begin(), s.end(), ':'), s.end());
	std::replace(s.begin(), s.end(), ' ', '-');
	return get_video_path() + "\\" + s + VR_VIDEO_EXT;
}

std::string config::create_new_capture_path() const
{
	auto s = now_to_string();
	s.erase(std::remove(s.begin(), s.end(), '-'), s.end());
	s.erase(std::remove(s.begin(), s.end(), ':'), s.end());
	std::replace(s.begin(), s.end(), ' ', '-');
	return get_capture_path() + "\\" + s + VR_CAPTRUE_EXT;
}

std::string config::get_thumb_path() const
{
	auto p = _root + "\\" + VR_THUMBNAIL_FOLDER;
	CreateDirectoryA(p.c_str(), nullptr);
	return p;
}

std::string config::create_new_thumb_path(const std::string & stem)
{
	auto p = get_thumb_path() + "\\" + stem + VR_THUMBNAIL_EXT;
	return p;
}

std::string config::get_thumb_of_video(const std::string & vpath)
{
	namespace fs = std::experimental::filesystem;
	auto thumb_path = create_new_thumb_path(fs::canonical(vpath).stem().string());
	if (fs::exists(thumb_path)) {
		return thumb_path;
	} else {
		using namespace cv;
		VideoCapture capture(vpath);
		if (capture.isOpened()) {
			Mat frame;
			capture >> frame; assert(!frame.empty());
			int c = frame.channels();
			//imshow("frame", frame);
			
			auto icon_play_path = utf8::w2a((CPaintManagerUI::GetResourcePath() + L"image\\play_128px.png").GetData());
			Mat icon = cv::imread(icon_play_path); assert(!icon.empty());
			//imshow("icon", icon);
			c = icon.channels();

			//Mat roi = frame(Range(frame.rows / 4, frame.rows * 3 / 4), Range(frame.cols / 4, frame.cols * 3 / 4));
			Mat roi = frame(Range(frame.rows / 2 - icon.rows / 2, frame.rows / 2 + icon.rows / 2), 
							Range(frame.cols / 2 - icon.cols / 2, frame.cols / 2 + icon.cols / 2));
			//imshow("roi", roi);

			//waitKey();
			auto alpha = 0.5;
			auto beta = 1.0 - alpha;
			addWeighted(roi, alpha, icon, beta, 0, roi);
			//bitwise_or(roi, icon, roi);

			// Now create a mask of logo and create its inverse mask also
			//Mat icon_gray;
			//cvtColor(icon, icon_gray, COLOR_BGR2GRAY);
			/*Mat mask;
			threshold(icon, mask, 30, 200, THRESH_BINARY);

			add(roi, icon, roi, mask);
*/

			////	ret, mask = cv2.threshold(img2gray, 10, 255, cv2.THRESH_BINARY)
			//Mat mask_inv;
			//bitwise_not(mask, mask_inv);
			//// Now black - out the area of logo in ROI
			////Mat roi_bg;
			//bitwise_and(roi, roi, roi, mask_inv);
			//// Take only region of logo from logo image.
			//Mat icon_fg;
			//bitwise_and(icon, icon, icon_fg, mask);
			//// Put logo in ROI and modify the main image
			////Mat roi_dst;
			//add(roi, icon_fg, roi);
			////roi = roi_dst;

			imwrite(thumb_path, frame);
			return thumb_path;
		}
	}

	return std::string();
}
