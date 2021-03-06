#pragma once
#include <iostream>
#include <cstdlib>

const std::string ASSETS_PATH = getenv("MASECZKI_BASE_DIR");
const std::string FACE_CASCADE = ASSETS_PATH + "/haarcascades/haarcascade_frontalface_default.xml";
const std::string EYE_PAIR_CASCADE = ASSETS_PATH + "/haarcascades/haarcascade_mcs_eyepair_big.xml";
const std::string MOUTH_CASCADE = ASSETS_PATH + "/haarcascades/haarcascade_mcs_mouth.xml";
const std::string NOSE_CASCADE = ASSETS_PATH + "/haarcascades/haarcascade_mcs_nose.xml";
const int PASS_PRECENTAGE_THRESHOLD = 50;
const int MINIMAL_FRAME_THRESHOLD = 60;

inline std::string ASSET_PATH(std::string path)
{
  return ASSETS_PATH + path;
}