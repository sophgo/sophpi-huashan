#pragma once

/**
 * @brief image pixel format
 */
typedef enum PixelFormat_t {
    Format_GRAY8 = 0,       ///< Gray8
    Format_RGB888,          ///< RGB888, packed
    Format_BGR888,          ///< BGR888, packed
    Format_YUV420P_YU12,    ///< YUV420P YU12: YYYYYYYYUUVV
    Format_YUV420P_YV12,    ///< YUV420P YV12: YYYYYYYYVVUU
    Format_YUV420SP_NV12,   ///< YUV420SP NV12: YYYYYYYYUVUV
    Format_YUV420SP_NV21,   ///< YUV420SP NV21: YYYYYYYYVUVU
    Format_MAX,
} PixelFormat;

/**
 * @brief image
 */
typedef struct Image_t {
    void* vir_addr;                     /* virtual address */
    void* phy_addr;                     /* physical address, not support */
    int fd;                             /* shared fd, not support */
    int width;                          /* width */
    int height;                         /* height */
    int wstride;                        /* wstride, support GRAY8/RGB888 packed/BGR888 packed/YUV420SP */
    int hstride;                        /* hstride, not support */
    PixelFormat pixel_format;                  ///< format (@ref rockface_pixel_format)
} Image;

typedef void* FaceHandle;
typedef void* FaceGroupHandle;

typedef enum FaceRetCode {
    RET_OK = 0,
    RET_INTERNAL_ERROR,
    RET_NO_FACE,
    RET_NULL_POINTER,
    RET_UNEXPECTED_MODEL,
    RET_BROKEN_FILE,
    RET_OUT_OF_RANGE,
    RET_FILE_NOT_FOUND,
    RET_INVALID_ARGUMENT,
    RET_UNAUTHORIZED,
    RET_UNSUPPORTED,
    RET_UNINITIALIZED,
    RET_NOT_FOUND,
    RET_DUP_INIT,
} FaceRetCode;

typedef enum Log_Level {
    LOG_LEVEL_ERROR = 1,
    LOG_LEVEL_INFO = 2,
} Log_Level ;

typedef struct FaceModels {
    const char *detect_model;
    const char *postfilter_model;
    const char *refine_model;
    const char *pose_blur_model;
    const char *stn_model;
    const char *feature_model;
    const char *liveness_ir_model;
    const char *liveness_bgr_model;
    const char *liveness_bgrir_model;
    const char *anchor_path;
    const char *group_model_path;
    const char *age_gender_model;
    const char *rc_model;
    const char *occl_model;
} FaceModels;

typedef struct Point {
    float x;
    float y;
} Point;

typedef struct Landmark {
    float score;
    Point points[81];
} Landmark;

typedef struct FaceRect {
    int left;
    int top;
    int right;
    int bottom;
} FaceRect;

typedef struct FacePose {
    float roll;
    float pitch;
    float yaw;
    float blur;
} FacePoseBlur;

typedef struct FaceAttr {
    float age;              // age
    float gender[2];        // ["male", "female"]

    float hair[5];          // [bald, little_hair, short_hair, long_hair, unknown]
    float beard[4];         // [no_beard, moustache, whisker, unknown]
    float hat[9];           // [no_hat, safety_helmet, chef_hat, student_hat, helmet, taoism_hat, kerchief, others, unknown]
    float respirator[7];    // [no_respirator, surgical, anti-pollution, common, kitchen_transparent, differ_respirator, unknown]
    float glasses[5];       // [no_glasses, glasses_with_dark_frame, regular_glasses, sunglasses, unknown]
    float skin_color[5];    // [yellow, white, black, brown, unknown]
} FaceAttr;

typedef struct FaceOccl {
    float leftEye[4];          // [no_occlusion, occlusion, unknown, eye_closed]
    float rightEye[4];          // [no_occlusion, occlusion, unknown, eye_closed]
    float nose[3];          // [no_occlusion, occlusion, unknown]
    float head[3];          // [no_occlusion, occlusion, unknown]
    float leftCheek[3];          // [no_occlusion, occlusion, unknown]
    float rightCheek[3];          // [no_occlusion, occlusion, unknown]
    float mouthAndChin[3];          // [no_occlusion, occlusion, unknown]
} FaceOccl;
