#include "lwip/apps/fs.h"
#include "lwip/def.h"
#include "fsdata.h"

#define file_NULL (struct fsdata_file *) NULL

static const unsigned int dummy_align__img_sics_gif = 0;
static const unsigned char data__img_sics_gif[] = {
/* /img/sics.gif (14 chars) */
0x2f, 0x69, 0x6d, 0x67, 0x2f, 0x73, 0x69, 0x63, 0x73, 0x2e, 0x67, 0x69, 0x66,
		0x00, 0x00, 0x00,

		/* HTTP header */
		/* "HTTP/1.0 200 OK
		 " (17 bytes) */
		0x48, 0x54, 0x54, 0x50, 0x2f, 0x31, 0x2e, 0x30, 0x20, 0x32, 0x30, 0x30,
		0x20, 0x4f, 0x4b, 0x0d, 0x0a,
		/* "Server: lwIP/1.3.1 (http://savannah.nongnu.org/projects/lwip)
		 " (63 bytes) */
		0x53, 0x65, 0x72, 0x76, 0x65, 0x72, 0x3a, 0x20, 0x6c, 0x77, 0x49, 0x50,
		0x2f, 0x31, 0x2e, 0x33, 0x2e, 0x31, 0x20, 0x28, 0x68, 0x74, 0x74, 0x70,
		0x3a, 0x2f, 0x2f, 0x73, 0x61, 0x76, 0x61, 0x6e, 0x6e, 0x61, 0x68, 0x2e,
		0x6e, 0x6f, 0x6e, 0x67, 0x6e, 0x75, 0x2e, 0x6f, 0x72, 0x67, 0x2f, 0x70,
		0x72, 0x6f, 0x6a, 0x65, 0x63, 0x74, 0x73, 0x2f, 0x6c, 0x77, 0x69, 0x70,
		0x29, 0x0d, 0x0a,
		/* "Content-type: image/gif

		 " (27 bytes) */
		0x43, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74, 0x2d, 0x74, 0x79, 0x70, 0x65,
		0x3a, 0x20, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x2f, 0x67, 0x69, 0x66, 0x0d,
		0x0a, 0x0d, 0x0a,
		/* raw file data (724 bytes) */
		0x47, 0x49, 0x46, 0x38, 0x39, 0x61, 0x46, 0x00, 0x22, 0x00, 0xa5, 0x00,
		0x00, 0xd9, 0x2b, 0x39, 0x6a, 0x6a, 0x6a, 0xbf, 0xbf, 0xbf, 0x93, 0x93,
		0x93, 0x0f, 0x0f, 0x0f, 0xb0, 0xb0, 0xb0, 0xa6, 0xa6, 0xa6, 0x80, 0x80,
		0x80, 0x76, 0x76, 0x76, 0x1e, 0x1e, 0x1e, 0x9d, 0x9d, 0x9d, 0x2e, 0x2e,
		0x2e, 0x49, 0x49, 0x49, 0x54, 0x54, 0x54, 0x8a, 0x8a, 0x8a, 0x60, 0x60,
		0x60, 0xc6, 0xa6, 0x99, 0xbd, 0xb5, 0xb2, 0xc2, 0xab, 0xa1, 0xd9, 0x41,
		0x40, 0xd5, 0x67, 0x55, 0xc0, 0xb0, 0xaa, 0xd5, 0x5e, 0x4e, 0xd6, 0x50,
		0x45, 0xcc, 0x93, 0x7d, 0xc8, 0xa1, 0x90, 0xce, 0x8b, 0x76, 0xd2, 0x7b,
		0x65, 0xd1, 0x84, 0x6d, 0xc9, 0x99, 0x86, 0x3a, 0x3a, 0x3a, 0x00, 0x00,
		0x00, 0xb8, 0xb8, 0xb8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x46, 0x00, 0x22, 0x00, 0x00, 0x06,
		0xfe, 0x40, 0x90, 0x70, 0x48, 0x2c, 0x1a, 0x8f, 0xc8, 0xa4, 0x72, 0xc9,
		0x6c, 0x3a, 0x9f, 0xd0, 0xa8, 0x74, 0x4a, 0xad, 0x5a, 0xaf, 0xd8, 0xac,
		0x76, 0xa9, 0x40, 0x04, 0xbe, 0x83, 0xe2, 0x60, 0x3c, 0x50, 0x20, 0x0d,
		0x8e, 0x6f, 0x00, 0x31, 0x28, 0x1c, 0x0d, 0x07, 0xb5, 0xc3, 0x60, 0x75,
		0x24, 0x3e, 0xf8, 0xfc, 0x87, 0x11, 0x06, 0xe9, 0x3d, 0x46, 0x07, 0x0b,
		0x7a, 0x7a, 0x7c, 0x43, 0x06, 0x1e, 0x84, 0x78, 0x0b, 0x07, 0x6e, 0x51,
		0x01, 0x8a, 0x84, 0x08, 0x7e, 0x79, 0x80, 0x87, 0x89, 0x91, 0x7a, 0x93,
		0x0a, 0x04, 0x99, 0x78, 0x96, 0x4f, 0x03, 0x9e, 0x79, 0x01, 0x94, 0x9f,
		0x43, 0x9c, 0xa3, 0xa4, 0x05, 0x77, 0xa3, 0xa0, 0x4e, 0x98, 0x79, 0x0b,
		0x1e, 0x83, 0xa4, 0xa6, 0x1f, 0x96, 0x05, 0x9d, 0xaa, 0x78, 0x01, 0x07,
		0x84, 0x04, 0x1e, 0x1e, 0xbb, 0xb8, 0x51, 0x84, 0x0e, 0x43, 0x05, 0x07,
		0x77, 0xa5, 0x7f, 0x42, 0xb1, 0xb2, 0x01, 0x63, 0x08, 0x0d, 0xbb, 0x01,
		0x0c, 0x7a, 0x0d, 0x44, 0x0e, 0xd8, 0xaf, 0x4c, 0x05, 0x7a, 0x04, 0x47,
		0x07, 0x07, 0xb7, 0x80, 0xa2, 0xe1, 0x7d, 0x44, 0x05, 0x01, 0x04, 0x01,
		0xd0, 0xea, 0x87, 0x93, 0x4f, 0xe0, 0x9a, 0x49, 0xce, 0xd8, 0x79, 0x04,
		0x66, 0x20, 0x15, 0x10, 0x10, 0x11, 0x92, 0x29, 0x80, 0xb6, 0xc0, 0x91,
		0x15, 0x45, 0x1e, 0x90, 0x19, 0x71, 0x46, 0xa8, 0x5c, 0x04, 0x0e, 0x00,
		0x22, 0x4e, 0xe8, 0x40, 0x24, 0x9f, 0x3e, 0x04, 0x06, 0xa7, 0x58, 0xd4,
		0x93, 0xa0, 0x1c, 0x91, 0x3f, 0xe8, 0xf0, 0x88, 0x03, 0xb1, 0x21, 0xa2,
		0x49, 0x00, 0x19, 0x86, 0xfc, 0x52, 0x44, 0xe0, 0x01, 0x9d, 0x29, 0x21,
		0x15, 0x25, 0x50, 0xf7, 0x67, 0x25, 0x1e, 0x06, 0xfd, 0x4e, 0x9a, 0xb4,
		0x90, 0xac, 0x15, 0xfa, 0xcb, 0x52, 0x53, 0x1e, 0x8c, 0xf2, 0xf8, 0x07,
		0x92, 0x2d, 0x08, 0x3a, 0x4d, 0x12, 0x49, 0x95, 0x49, 0xdb, 0x14, 0x04,
		0xc4, 0x14, 0x85, 0x29, 0xaa, 0xe7, 0x01, 0x08, 0xa4, 0x49, 0x01, 0x14,
		0x51, 0xe0, 0x53, 0x91, 0xd5, 0x29, 0x06, 0x1a, 0x64, 0x02, 0xf4, 0xc7,
		0x81, 0x9e, 0x05, 0x20, 0x22, 0x64, 0xa5, 0x30, 0xae, 0xab, 0x9e, 0x97,
		0x53, 0xd8, 0xb9, 0xfd, 0x50, 0xef, 0x93, 0x02, 0x42, 0x74, 0x34, 0xe8,
		0x9c, 0x20, 0x21, 0xc9, 0x01, 0x68, 0x78, 0xe6, 0x55, 0x29, 0x20, 0x56,
		0x4f, 0x4c, 0x40, 0x51, 0x71, 0x82, 0xc0, 0x70, 0x21, 0x22, 0x85, 0xbe,
		0x4b, 0x1c, 0x44, 0x05, 0xea, 0xa4, 0x01, 0xbf, 0x22, 0xb5, 0xf0, 0x1c,
		0x06, 0x51, 0x38, 0x8f, 0xe0, 0x22, 0xec, 0x18, 0xac, 0x39, 0x22, 0xd4,
		0xd6, 0x93, 0x44, 0x01, 0x32, 0x82, 0xc8, 0xfc, 0x61, 0xb3, 0x01, 0x45,
		0x0c, 0x2e, 0x83, 0x30, 0xd0, 0x0e, 0x17, 0x24, 0x0f, 0x70, 0x85, 0x94,
		0xee, 0x05, 0x05, 0x53, 0x4b, 0x32, 0x1b, 0x3f, 0x98, 0xd3, 0x1d, 0x29,
		0x81, 0xb0, 0xae, 0x1e, 0x8c, 0x7e, 0x68, 0xe0, 0x60, 0x5a, 0x54, 0x8f,
		0xb0, 0x78, 0x69, 0x73, 0x06, 0xa2, 0x00, 0x6b, 0x57, 0xca, 0x3d, 0x11,
		0x50, 0xbd, 0x04, 0x30, 0x4b, 0x3a, 0xd4, 0xab, 0x5f, 0x1f, 0x9b, 0x3d,
		0x13, 0x74, 0x27, 0x88, 0x3c, 0x25, 0xe0, 0x17, 0xbe, 0x7a, 0x79, 0x45,
		0x0d, 0x0c, 0xb0, 0x8b, 0xda, 0x90, 0xca, 0x80, 0x06, 0x5d, 0x17, 0x60,
		0x1c, 0x22, 0x4c, 0xd8, 0x57, 0x22, 0x06, 0x20, 0x00, 0x98, 0x07, 0x08,
		0xe4, 0x56, 0x80, 0x80, 0x1c, 0xc5, 0xb7, 0xc5, 0x82, 0x0c, 0x36, 0xe8,
		0xe0, 0x83, 0x10, 0x46, 0x28, 0xe1, 0x84, 0x14, 0x56, 0x68, 0xa1, 0x10,
		0x41, 0x00, 0x00, 0x3b, };

static const unsigned int dummy_align__404_html = 1;
static const unsigned char data__404_html[] = {
/* /404.html (10 chars) */
0x2f, 0x34, 0x30, 0x34, 0x2e, 0x68, 0x74, 0x6d, 0x6c, 0x00, 0x00, 0x00,

/* HTTP header */
/* "HTTP/1.0 404 File not found
 " (29 bytes) */
0x48, 0x54, 0x54, 0x50, 0x2f, 0x31, 0x2e, 0x30, 0x20, 0x34, 0x30, 0x34, 0x20,
		0x46, 0x69, 0x6c, 0x65, 0x20, 0x6e, 0x6f, 0x74, 0x20, 0x66, 0x6f, 0x75,
		0x6e, 0x64, 0x0d, 0x0a,
		/* "Server: lwIP/1.3.1 (http://savannah.nongnu.org/projects/lwip)
		 " (63 bytes) */
		0x53, 0x65, 0x72, 0x76, 0x65, 0x72, 0x3a, 0x20, 0x6c, 0x77, 0x49, 0x50,
		0x2f, 0x31, 0x2e, 0x33, 0x2e, 0x31, 0x20, 0x28, 0x68, 0x74, 0x74, 0x70,
		0x3a, 0x2f, 0x2f, 0x73, 0x61, 0x76, 0x61, 0x6e, 0x6e, 0x61, 0x68, 0x2e,
		0x6e, 0x6f, 0x6e, 0x67, 0x6e, 0x75, 0x2e, 0x6f, 0x72, 0x67, 0x2f, 0x70,
		0x72, 0x6f, 0x6a, 0x65, 0x63, 0x74, 0x73, 0x2f, 0x6c, 0x77, 0x69, 0x70,
		0x29, 0x0d, 0x0a,
		/* "Content-type: text/html

		 " (27 bytes) */
		0x43, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74, 0x2d, 0x74, 0x79, 0x70, 0x65,
		0x3a, 0x20, 0x74, 0x65, 0x78, 0x74, 0x2f, 0x68, 0x74, 0x6d, 0x6c, 0x0d,
		0x0a, 0x0d, 0x0a,
		/* raw file data (565 bytes) */
		0x3c, 0x68, 0x74, 0x6d, 0x6c, 0x3e, 0x0d, 0x0a, 0x3c, 0x68, 0x65, 0x61,
		0x64, 0x3e, 0x3c, 0x74, 0x69, 0x74, 0x6c, 0x65, 0x3e, 0x6c, 0x77, 0x49,
		0x50, 0x20, 0x2d, 0x20, 0x41, 0x20, 0x4c, 0x69, 0x67, 0x68, 0x74, 0x77,
		0x65, 0x69, 0x67, 0x68, 0x74, 0x20, 0x54, 0x43, 0x50, 0x2f, 0x49, 0x50,
		0x20, 0x53, 0x74, 0x61, 0x63, 0x6b, 0x3c, 0x2f, 0x74, 0x69, 0x74, 0x6c,
		0x65, 0x3e, 0x3c, 0x2f, 0x68, 0x65, 0x61, 0x64, 0x3e, 0x0d, 0x0a, 0x3c,
		0x62, 0x6f, 0x64, 0x79, 0x20, 0x62, 0x67, 0x63, 0x6f, 0x6c, 0x6f, 0x72,
		0x3d, 0x22, 0x77, 0x68, 0x69, 0x74, 0x65, 0x22, 0x20, 0x74, 0x65, 0x78,
		0x74, 0x3d, 0x22, 0x62, 0x6c, 0x61, 0x63, 0x6b, 0x22, 0x3e, 0x0d, 0x0a,
		0x0d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x74, 0x61, 0x62, 0x6c, 0x65,
		0x20, 0x77, 0x69, 0x64, 0x74, 0x68, 0x3d, 0x22, 0x31, 0x30, 0x30, 0x25,
		0x22, 0x3e, 0x0d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x74,
		0x72, 0x20, 0x76, 0x61, 0x6c, 0x69, 0x67, 0x6e, 0x3d, 0x22, 0x74, 0x6f,
		0x70, 0x22, 0x3e, 0x3c, 0x74, 0x64, 0x20, 0x77, 0x69, 0x64, 0x74, 0x68,
		0x3d, 0x22, 0x38, 0x30, 0x22, 0x3e, 0x09, 0x20, 0x20, 0x0d, 0x0a, 0x09,
		0x20, 0x20, 0x3c, 0x61, 0x20, 0x68, 0x72, 0x65, 0x66, 0x3d, 0x22, 0x68,
		0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x73, 0x69,
		0x63, 0x73, 0x2e, 0x73, 0x65, 0x2f, 0x22, 0x3e, 0x3c, 0x69, 0x6d, 0x67,
		0x20, 0x73, 0x72, 0x63, 0x3d, 0x22, 0x2f, 0x69, 0x6d, 0x67, 0x2f, 0x73,
		0x69, 0x63, 0x73, 0x2e, 0x67, 0x69, 0x66, 0x22, 0x0d, 0x0a, 0x09, 0x20,
		0x20, 0x62, 0x6f, 0x72, 0x64, 0x65, 0x72, 0x3d, 0x22, 0x30, 0x22, 0x20,
		0x61, 0x6c, 0x74, 0x3d, 0x22, 0x53, 0x49, 0x43, 0x53, 0x20, 0x6c, 0x6f,
		0x67, 0x6f, 0x22, 0x20, 0x74, 0x69, 0x74, 0x6c, 0x65, 0x3d, 0x22, 0x53,
		0x49, 0x43, 0x53, 0x20, 0x6c, 0x6f, 0x67, 0x6f, 0x22, 0x3e, 0x3c, 0x2f,
		0x61, 0x3e, 0x0d, 0x0a, 0x09, 0x3c, 0x2f, 0x74, 0x64, 0x3e, 0x3c, 0x74,
		0x64, 0x20, 0x77, 0x69, 0x64, 0x74, 0x68, 0x3d, 0x22, 0x35, 0x30, 0x30,
		0x22, 0x3e, 0x09, 0x20, 0x20, 0x0d, 0x0a, 0x09, 0x20, 0x20, 0x3c, 0x68,
		0x31, 0x3e, 0x6c, 0x77, 0x49, 0x50, 0x20, 0x2d, 0x20, 0x41, 0x20, 0x4c,
		0x69, 0x67, 0x68, 0x74, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x20, 0x54,
		0x43, 0x50, 0x2f, 0x49, 0x50, 0x20, 0x53, 0x74, 0x61, 0x63, 0x6b, 0x3c,
		0x2f, 0x68, 0x31, 0x3e, 0x0d, 0x0a, 0x09, 0x20, 0x20, 0x3c, 0x68, 0x32,
		0x3e, 0x34, 0x30, 0x34, 0x20, 0x2d, 0x20, 0x50, 0x61, 0x67, 0x65, 0x20,
		0x6e, 0x6f, 0x74, 0x20, 0x66, 0x6f, 0x75, 0x6e, 0x64, 0x3c, 0x2f, 0x68,
		0x32, 0x3e, 0x0d, 0x0a, 0x09, 0x20, 0x20, 0x3c, 0x70, 0x3e, 0x0d, 0x0a,
		0x09, 0x20, 0x20, 0x20, 0x20, 0x53, 0x6f, 0x72, 0x72, 0x79, 0x2c, 0x20,
		0x74, 0x68, 0x65, 0x20, 0x70, 0x61, 0x67, 0x65, 0x20, 0x79, 0x6f, 0x75,
		0x20, 0x61, 0x72, 0x65, 0x20, 0x72, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74,
		0x69, 0x6e, 0x67, 0x20, 0x77, 0x61, 0x73, 0x20, 0x6e, 0x6f, 0x74, 0x20,
		0x66, 0x6f, 0x75, 0x6e, 0x64, 0x20, 0x6f, 0x6e, 0x20, 0x74, 0x68, 0x69,
		0x73, 0x0d, 0x0a, 0x09, 0x20, 0x20, 0x20, 0x20, 0x73, 0x65, 0x72, 0x76,
		0x65, 0x72, 0x2e, 0x20, 0x0d, 0x0a, 0x09, 0x20, 0x20, 0x3c, 0x2f, 0x70,
		0x3e, 0x0d, 0x0a, 0x09, 0x3c, 0x2f, 0x74, 0x64, 0x3e, 0x3c, 0x74, 0x64,
		0x3e, 0x0d, 0x0a, 0x09, 0x20, 0x20, 0x26, 0x6e, 0x62, 0x73, 0x70, 0x3b,
		0x0d, 0x0a, 0x09, 0x3c, 0x2f, 0x74, 0x64, 0x3e, 0x3c, 0x2f, 0x74, 0x72,
		0x3e, 0x0d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x2f, 0x74,
		0x61, 0x62, 0x6c, 0x65, 0x3e, 0x0d, 0x0a, 0x3c, 0x2f, 0x62, 0x6f, 0x64,
		0x79, 0x3e, 0x0d, 0x0a, 0x3c, 0x2f, 0x68, 0x74, 0x6d, 0x6c, 0x3e, 0x0d,
		0x0a, };

static const unsigned int dummy_align__index_html = 2;
static const unsigned char data__index_html[] = {
/* /index.html (12 chars) */
0x2f, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x2e, 0x68, 0x74, 0x6d, 0x6c, 0x00,

/* HTTP header */
/* "HTTP/1.0 200 OK
 " (17 bytes) */
0x48, 0x54, 0x54, 0x50, 0x2f, 0x31, 0x2e, 0x30, 0x20, 0x32, 0x30, 0x30, 0x20,
		0x4f, 0x4b, 0x0d, 0x0a,
		/* "Server: lwIP/1.3.1 (http://savannah.nongnu.org/projects/lwip)
		 " (63 bytes) */
		0x53, 0x65, 0x72, 0x76, 0x65, 0x72, 0x3a, 0x20, 0x6c, 0x77, 0x49, 0x50,
		0x2f, 0x31, 0x2e, 0x33, 0x2e, 0x31, 0x20, 0x28, 0x68, 0x74, 0x74, 0x70,
		0x3a, 0x2f, 0x2f, 0x73, 0x61, 0x76, 0x61, 0x6e, 0x6e, 0x61, 0x68, 0x2e,
		0x6e, 0x6f, 0x6e, 0x67, 0x6e, 0x75, 0x2e, 0x6f, 0x72, 0x67, 0x2f, 0x70,
		0x72, 0x6f, 0x6a, 0x65, 0x63, 0x74, 0x73, 0x2f, 0x6c, 0x77, 0x69, 0x70,
		0x29, 0x0d, 0x0a,
		/* "Content-type: text/html

		 " (27 bytes) */
		0x43, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74, 0x2d, 0x74, 0x79, 0x70, 0x65,
		0x3a, 0x20, 0x74, 0x65, 0x78, 0x74, 0x2f, 0x68, 0x74, 0x6d, 0x6c, 0x0d,
		0x0a, 0x0d, 0x0a,
		/* raw file data (1751 bytes) */
		0x3c, 0x68, 0x74, 0x6d, 0x6c, 0x3e, 0x0d, 0x0a, 0x3c, 0x68, 0x65, 0x61,
		0x64, 0x3e, 0x3c, 0x74, 0x69, 0x74, 0x6c, 0x65, 0x3e, 0x6c, 0x77, 0x49,
		0x50, 0x20, 0x2d, 0x20, 0x41, 0x20, 0x4c, 0x69, 0x67, 0x68, 0x74, 0x77,
		0x65, 0x69, 0x67, 0x68, 0x74, 0x20, 0x54, 0x43, 0x50, 0x2f, 0x49, 0x50,
		0x20, 0x53, 0x74, 0x61, 0x63, 0x6b, 0x3c, 0x2f, 0x74, 0x69, 0x74, 0x6c,
		0x65, 0x3e, 0x3c, 0x2f, 0x68, 0x65, 0x61, 0x64, 0x3e, 0x0d, 0x0a, 0x3c,
		0x62, 0x6f, 0x64, 0x79, 0x20, 0x62, 0x67, 0x63, 0x6f, 0x6c, 0x6f, 0x72,
		0x3d, 0x22, 0x77, 0x68, 0x69, 0x74, 0x65, 0x22, 0x20, 0x74, 0x65, 0x78,
		0x74, 0x3d, 0x22, 0x62, 0x6c, 0x61, 0x63, 0x6b, 0x22, 0x3e, 0x0d, 0x0a,
		0x0d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x74, 0x61, 0x62, 0x6c, 0x65,
		0x20, 0x77, 0x69, 0x64, 0x74, 0x68, 0x3d, 0x22, 0x31, 0x30, 0x30, 0x25,
		0x22, 0x3e, 0x0d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x74,
		0x72, 0x20, 0x76, 0x61, 0x6c, 0x69, 0x67, 0x6e, 0x3d, 0x22, 0x74, 0x6f,
		0x70, 0x22, 0x3e, 0x3c, 0x74, 0x64, 0x20, 0x77, 0x69, 0x64, 0x74, 0x68,
		0x3d, 0x22, 0x38, 0x30, 0x22, 0x3e, 0x09, 0x20, 0x20, 0x0d, 0x0a, 0x09,
		0x20, 0x20, 0x3c, 0x61, 0x20, 0x68, 0x72, 0x65, 0x66, 0x3d, 0x22, 0x68,
		0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x73, 0x69,
		0x63, 0x73, 0x2e, 0x73, 0x65, 0x2f, 0x22, 0x3e, 0x3c, 0x69, 0x6d, 0x67,
		0x20, 0x73, 0x72, 0x63, 0x3d, 0x22, 0x2f, 0x69, 0x6d, 0x67, 0x2f, 0x73,
		0x69, 0x63, 0x73, 0x2e, 0x67, 0x69, 0x66, 0x22, 0x0d, 0x0a, 0x09, 0x20,
		0x20, 0x62, 0x6f, 0x72, 0x64, 0x65, 0x72, 0x3d, 0x22, 0x30, 0x22, 0x20,
		0x61, 0x6c, 0x74, 0x3d, 0x22, 0x53, 0x49, 0x43, 0x53, 0x20, 0x6c, 0x6f,
		0x67, 0x6f, 0x22, 0x20, 0x74, 0x69, 0x74, 0x6c, 0x65, 0x3d, 0x22, 0x53,
		0x49, 0x43, 0x53, 0x20, 0x6c, 0x6f, 0x67, 0x6f, 0x22, 0x3e, 0x3c, 0x2f,
		0x61, 0x3e, 0x0d, 0x0a, 0x09, 0x3c, 0x2f, 0x74, 0x64, 0x3e, 0x3c, 0x74,
		0x64, 0x20, 0x77, 0x69, 0x64, 0x74, 0x68, 0x3d, 0x22, 0x35, 0x30, 0x30,
		0x22, 0x3e, 0x09, 0x20, 0x20, 0x0d, 0x0a, 0x09, 0x20, 0x20, 0x3c, 0x68,
		0x31, 0x3e, 0x6c, 0x77, 0x49, 0x50, 0x20, 0x2d, 0x20, 0x41, 0x20, 0x4c,
		0x69, 0x67, 0x68, 0x74, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x20, 0x54,
		0x43, 0x50, 0x2f, 0x49, 0x50, 0x20, 0x53, 0x74, 0x61, 0x63, 0x6b, 0x3c,
		0x2f, 0x68, 0x31, 0x3e, 0x0d, 0x0a, 0x09, 0x20, 0x20, 0x3c, 0x70, 0x3e,
		0x0d, 0x0a, 0x09, 0x20, 0x20, 0x20, 0x20, 0x54, 0x68, 0x65, 0x20, 0x77,
		0x65, 0x62, 0x20, 0x70, 0x61, 0x67, 0x65, 0x20, 0x79, 0x6f, 0x75, 0x20,
		0x61, 0x72, 0x65, 0x20, 0x77, 0x61, 0x74, 0x63, 0x68, 0x69, 0x6e, 0x67,
		0x20, 0x77, 0x61, 0x73, 0x20, 0x73, 0x65, 0x72, 0x76, 0x65, 0x64, 0x20,
		0x62, 0x79, 0x20, 0x61, 0x20, 0x73, 0x69, 0x6d, 0x70, 0x6c, 0x65, 0x20,
		0x77, 0x65, 0x62, 0x0d, 0x0a, 0x09, 0x20, 0x20, 0x20, 0x20, 0x73, 0x65,
		0x72, 0x76, 0x65, 0x72, 0x20, 0x72, 0x75, 0x6e, 0x6e, 0x69, 0x6e, 0x67,
		0x20, 0x6f, 0x6e, 0x20, 0x74, 0x6f, 0x70, 0x20, 0x6f, 0x66, 0x20, 0x74,
		0x68, 0x65, 0x20, 0x6c, 0x69, 0x67, 0x68, 0x74, 0x77, 0x65, 0x69, 0x67,
		0x68, 0x74, 0x20, 0x54, 0x43, 0x50, 0x2f, 0x49, 0x50, 0x20, 0x73, 0x74,
		0x61, 0x63, 0x6b, 0x20, 0x3c, 0x61, 0x0d, 0x0a, 0x09, 0x20, 0x20, 0x20,
		0x20, 0x68, 0x72, 0x65, 0x66, 0x3d, 0x22, 0x68, 0x74, 0x74, 0x70, 0x3a,
		0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x73, 0x69, 0x63, 0x73, 0x2e, 0x73,
		0x65, 0x2f, 0x7e, 0x61, 0x64, 0x61, 0x6d, 0x2f, 0x6c, 0x77, 0x69, 0x70,
		0x2f, 0x22, 0x3e, 0x6c, 0x77, 0x49, 0x50, 0x3c, 0x2f, 0x61, 0x3e, 0x2e,
		0x0d, 0x0a, 0x09, 0x20, 0x20, 0x3c, 0x2f, 0x70, 0x3e, 0x0d, 0x0a, 0x09,
		0x20, 0x20, 0x3c, 0x70, 0x3e, 0x0d, 0x0a, 0x09, 0x20, 0x20, 0x20, 0x20,
		0x6c, 0x77, 0x49, 0x50, 0x20, 0x69, 0x73, 0x20, 0x61, 0x6e, 0x20, 0x6f,
		0x70, 0x65, 0x6e, 0x20, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x20, 0x69,
		0x6d, 0x70, 0x6c, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x61, 0x74, 0x69, 0x6f,
		0x6e, 0x20, 0x6f, 0x66, 0x20, 0x74, 0x68, 0x65, 0x20, 0x54, 0x43, 0x50,
		0x2f, 0x49, 0x50, 0x0d, 0x0a, 0x09, 0x20, 0x20, 0x20, 0x20, 0x70, 0x72,
		0x6f, 0x74, 0x6f, 0x63, 0x6f, 0x6c, 0x20, 0x73, 0x75, 0x69, 0x74, 0x65,
		0x20, 0x74, 0x68, 0x61, 0x74, 0x20, 0x77, 0x61, 0x73, 0x20, 0x6f, 0x72,
		0x69, 0x67, 0x69, 0x6e, 0x61, 0x6c, 0x6c, 0x79, 0x20, 0x77, 0x72, 0x69,
		0x74, 0x74, 0x65, 0x6e, 0x20, 0x62, 0x79, 0x20, 0x3c, 0x61, 0x0d, 0x0a,
		0x09, 0x20, 0x20, 0x20, 0x20, 0x68, 0x72, 0x65, 0x66, 0x3d, 0x22, 0x68,
		0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x73, 0x69,
		0x63, 0x73, 0x2e, 0x73, 0x65, 0x2f, 0x7e, 0x61, 0x64, 0x61, 0x6d, 0x2f,
		0x6c, 0x77, 0x69, 0x70, 0x2f, 0x22, 0x3e, 0x41, 0x64, 0x61, 0x6d, 0x20,
		0x44, 0x75, 0x6e, 0x6b, 0x65, 0x6c, 0x73, 0x0d, 0x0a, 0x09, 0x20, 0x20,
		0x20, 0x20, 0x6f, 0x66, 0x20, 0x74, 0x68, 0x65, 0x20, 0x53, 0x77, 0x65,
		0x64, 0x69, 0x73, 0x68, 0x20, 0x49, 0x6e, 0x73, 0x74, 0x69, 0x74, 0x75,
		0x74, 0x65, 0x20, 0x6f, 0x66, 0x20, 0x43, 0x6f, 0x6d, 0x70, 0x75, 0x74,
		0x65, 0x72, 0x20, 0x53, 0x63, 0x69, 0x65, 0x6e, 0x63, 0x65, 0x3c, 0x2f,
		0x61, 0x3e, 0x20, 0x62, 0x75, 0x74, 0x20, 0x6e, 0x6f, 0x77, 0x20, 0x69,
		0x73, 0x0d, 0x0a, 0x09, 0x20, 0x20, 0x20, 0x20, 0x62, 0x65, 0x69, 0x6e,
		0x67, 0x20, 0x61, 0x63, 0x74, 0x69, 0x76, 0x65, 0x6c, 0x79, 0x20, 0x64,
		0x65, 0x76, 0x65, 0x6c, 0x6f, 0x70, 0x65, 0x64, 0x20, 0x62, 0x79, 0x20,
		0x61, 0x20, 0x74, 0x65, 0x61, 0x6d, 0x20, 0x6f, 0x66, 0x20, 0x64, 0x65,
		0x76, 0x65, 0x6c, 0x6f, 0x70, 0x65, 0x72, 0x73, 0x0d, 0x0a, 0x09, 0x20,
		0x20, 0x20, 0x20, 0x64, 0x69, 0x73, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74,
		0x65, 0x64, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x2d, 0x77, 0x69, 0x64,
		0x65, 0x2e, 0x20, 0x53, 0x69, 0x6e, 0x63, 0x65, 0x20, 0x69, 0x74, 0x27,
		0x73, 0x20, 0x72, 0x65, 0x6c, 0x65, 0x61, 0x73, 0x65, 0x2c, 0x20, 0x6c,
		0x77, 0x49, 0x50, 0x20, 0x68, 0x61, 0x73, 0x0d, 0x0a, 0x09, 0x20, 0x20,
		0x20, 0x20, 0x73, 0x70, 0x75, 0x72, 0x72, 0x65, 0x64, 0x20, 0x61, 0x20,
		0x6c, 0x6f, 0x74, 0x20, 0x6f, 0x66, 0x20, 0x69, 0x6e, 0x74, 0x65, 0x72,
		0x65, 0x73, 0x74, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x68, 0x61, 0x73, 0x20,
		0x62, 0x65, 0x65, 0x6e, 0x20, 0x70, 0x6f, 0x72, 0x74, 0x65, 0x64, 0x20,
		0x74, 0x6f, 0x20, 0x73, 0x65, 0x76, 0x65, 0x72, 0x61, 0x6c, 0x0d, 0x0a,
		0x09, 0x20, 0x20, 0x20, 0x20, 0x70, 0x6c, 0x61, 0x74, 0x66, 0x6f, 0x72,
		0x6d, 0x73, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x6f, 0x70, 0x65, 0x72, 0x61,
		0x74, 0x69, 0x6e, 0x67, 0x20, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6d, 0x73,
		0x2e, 0x20, 0x6c, 0x77, 0x49, 0x50, 0x20, 0x63, 0x61, 0x6e, 0x20, 0x62,
		0x65, 0x20, 0x75, 0x73, 0x65, 0x64, 0x20, 0x65, 0x69, 0x74, 0x68, 0x65,
		0x72, 0x0d, 0x0a, 0x09, 0x20, 0x20, 0x20, 0x20, 0x77, 0x69, 0x74, 0x68,
		0x20, 0x6f, 0x72, 0x20, 0x77, 0x69, 0x74, 0x68, 0x6f, 0x75, 0x74, 0x20,
		0x61, 0x6e, 0x20, 0x75, 0x6e, 0x64, 0x65, 0x72, 0x6c, 0x79, 0x69, 0x6e,
		0x67, 0x20, 0x4f, 0x53, 0x2e, 0x0d, 0x0a, 0x09, 0x20, 0x20, 0x3c, 0x2f,
		0x70, 0x3e, 0x0d, 0x0a, 0x09, 0x20, 0x20, 0x3c, 0x70, 0x3e, 0x0d, 0x0a,
		0x09, 0x20, 0x20, 0x20, 0x20, 0x54, 0x68, 0x65, 0x20, 0x66, 0x6f, 0x63,
		0x75, 0x73, 0x20, 0x6f, 0x66, 0x20, 0x74, 0x68, 0x65, 0x20, 0x6c, 0x77,
		0x49, 0x50, 0x20, 0x54, 0x43, 0x50, 0x2f, 0x49, 0x50, 0x20, 0x69, 0x6d,
		0x70, 0x6c, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x61, 0x74, 0x69, 0x6f, 0x6e,
		0x20, 0x69, 0x73, 0x20, 0x74, 0x6f, 0x20, 0x72, 0x65, 0x64, 0x75, 0x63,
		0x65, 0x0d, 0x0a, 0x09, 0x20, 0x20, 0x20, 0x20, 0x74, 0x68, 0x65, 0x20,
		0x52, 0x41, 0x4d, 0x20, 0x75, 0x73, 0x61, 0x67, 0x65, 0x20, 0x77, 0x68,
		0x69, 0x6c, 0x65, 0x20, 0x73, 0x74, 0x69, 0x6c, 0x6c, 0x20, 0x68, 0x61,
		0x76, 0x69, 0x6e, 0x67, 0x20, 0x61, 0x20, 0x66, 0x75, 0x6c, 0x6c, 0x20,
		0x73, 0x63, 0x61, 0x6c, 0x65, 0x20, 0x54, 0x43, 0x50, 0x2e, 0x20, 0x54,
		0x68, 0x69, 0x73, 0x0d, 0x0a, 0x09, 0x20, 0x20, 0x20, 0x20, 0x6d, 0x61,
		0x6b, 0x65, 0x73, 0x20, 0x6c, 0x77, 0x49, 0x50, 0x20, 0x73, 0x75, 0x69,
		0x74, 0x61, 0x62, 0x6c, 0x65, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x75, 0x73,
		0x65, 0x20, 0x69, 0x6e, 0x20, 0x65, 0x6d, 0x62, 0x65, 0x64, 0x64, 0x65,
		0x64, 0x20, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6d, 0x73, 0x20, 0x77, 0x69,
		0x74, 0x68, 0x20, 0x74, 0x65, 0x6e, 0x73, 0x0d, 0x0a, 0x09, 0x20, 0x20,
		0x20, 0x20, 0x6f, 0x66, 0x20, 0x6b, 0x69, 0x6c, 0x6f, 0x62, 0x79, 0x74,
		0x65, 0x73, 0x20, 0x6f, 0x66, 0x20, 0x66, 0x72, 0x65, 0x65, 0x20, 0x52,
		0x41, 0x4d, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x72, 0x6f, 0x6f, 0x6d, 0x20,
		0x66, 0x6f, 0x72, 0x20, 0x61, 0x72, 0x6f, 0x75, 0x6e, 0x64, 0x20, 0x34,
		0x30, 0x20, 0x6b, 0x69, 0x6c, 0x6f, 0x62, 0x79, 0x74, 0x65, 0x73, 0x0d,
		0x0a, 0x09, 0x20, 0x20, 0x20, 0x20, 0x6f, 0x66, 0x20, 0x63, 0x6f, 0x64,
		0x65, 0x20, 0x52, 0x4f, 0x4d, 0x2e, 0x0d, 0x0a, 0x09, 0x20, 0x20, 0x3c,
		0x2f, 0x70, 0x3e, 0x0d, 0x0a, 0x09, 0x20, 0x20, 0x3c, 0x70, 0x3e, 0x0d,
		0x0a, 0x09, 0x20, 0x20, 0x20, 0x20, 0x4d, 0x6f, 0x72, 0x65, 0x20, 0x69,
		0x6e, 0x66, 0x6f, 0x72, 0x6d, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x61,
		0x62, 0x6f, 0x75, 0x74, 0x20, 0x6c, 0x77, 0x49, 0x50, 0x20, 0x63, 0x61,
		0x6e, 0x20, 0x62, 0x65, 0x20, 0x66, 0x6f, 0x75, 0x6e, 0x64, 0x20, 0x61,
		0x74, 0x20, 0x74, 0x68, 0x65, 0x20, 0x6c, 0x77, 0x49, 0x50, 0x0d, 0x0a,
		0x09, 0x20, 0x20, 0x20, 0x20, 0x68, 0x6f, 0x6d, 0x65, 0x70, 0x61, 0x67,
		0x65, 0x20, 0x61, 0x74, 0x20, 0x3c, 0x61, 0x0d, 0x0a, 0x09, 0x20, 0x20,
		0x20, 0x20, 0x68, 0x72, 0x65, 0x66, 0x3d, 0x22, 0x68, 0x74, 0x74, 0x70,
		0x3a, 0x2f, 0x2f, 0x73, 0x61, 0x76, 0x61, 0x6e, 0x6e, 0x61, 0x68, 0x2e,
		0x6e, 0x6f, 0x6e, 0x67, 0x6e, 0x75, 0x2e, 0x6f, 0x72, 0x67, 0x2f, 0x70,
		0x72, 0x6f, 0x6a, 0x65, 0x63, 0x74, 0x73, 0x2f, 0x6c, 0x77, 0x69, 0x70,
		0x2f, 0x22, 0x3e, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x73, 0x61,
		0x76, 0x61, 0x6e, 0x6e, 0x61, 0x68, 0x2e, 0x6e, 0x6f, 0x6e, 0x67, 0x6e,
		0x75, 0x2e, 0x6f, 0x72, 0x67, 0x2f, 0x70, 0x72, 0x6f, 0x6a, 0x65, 0x63,
		0x74, 0x73, 0x2f, 0x6c, 0x77, 0x69, 0x70, 0x2f, 0x3c, 0x2f, 0x61, 0x3e,
		0x0d, 0x0a, 0x09, 0x20, 0x20, 0x20, 0x20, 0x6f, 0x72, 0x20, 0x61, 0x74,
		0x20, 0x74, 0x68, 0x65, 0x20, 0x6c, 0x77, 0x49, 0x50, 0x20, 0x77, 0x69,
		0x6b, 0x69, 0x20, 0x61, 0x74, 0x20, 0x3c, 0x61, 0x0d, 0x0a, 0x09, 0x20,
		0x20, 0x20, 0x20, 0x68, 0x72, 0x65, 0x66, 0x3d, 0x22, 0x68, 0x74, 0x74,
		0x70, 0x3a, 0x2f, 0x2f, 0x6c, 0x77, 0x69, 0x70, 0x2e, 0x77, 0x69, 0x6b,
		0x69, 0x61, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x22, 0x3e, 0x68, 0x74, 0x74,
		0x70, 0x3a, 0x2f, 0x2f, 0x6c, 0x77, 0x69, 0x70, 0x2e, 0x77, 0x69, 0x6b,
		0x69, 0x61, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x3c, 0x2f, 0x61, 0x3e, 0x2e,
		0x0d, 0x0a, 0x09, 0x20, 0x20, 0x3c, 0x2f, 0x70, 0x3e, 0x0d, 0x0a, 0x09,
		0x3c, 0x2f, 0x74, 0x64, 0x3e, 0x3c, 0x74, 0x64, 0x3e, 0x0d, 0x0a, 0x09,
		0x20, 0x20, 0x26, 0x6e, 0x62, 0x73, 0x70, 0x3b, 0x0d, 0x0a, 0x09, 0x3c,
		0x2f, 0x74, 0x64, 0x3e, 0x3c, 0x2f, 0x74, 0x72, 0x3e, 0x0d, 0x0a, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x2f, 0x74, 0x61, 0x62, 0x6c, 0x65,
		0x3e, 0x0d, 0x0a, 0x3c, 0x2f, 0x62, 0x6f, 0x64, 0x79, 0x3e, 0x0d, 0x0a,
		0x3c, 0x2f, 0x68, 0x74, 0x6d, 0x6c, 0x3e, 0x0d, 0x0a, 0x0d, 0x0a, };

const struct fsdata_file file__img_sics_gif[] = { {
file_NULL, data__img_sics_gif, data__img_sics_gif + 16,
		sizeof(data__img_sics_gif) - 16, 1, } };

const struct fsdata_file file__404_html[] = { { file__img_sics_gif,
		data__404_html, data__404_html + 12, sizeof(data__404_html) - 12, 1, } };

const struct fsdata_file file__index_html[] = { { file__404_html,
		data__index_html, data__index_html + 12, sizeof(data__index_html) - 12,
		1, } };

#define FS_ROOT file__index_html
#define FS_NUMFILES 3

#include "ff.h"
#include "stdio.h"

FIL fp; //This line was added later

int fs_open_custom(struct fs_file *file, const char name[]) {
	char Buff[256];
	//return 0;

	unsigned int Cnt;
	FRESULT fr;
	PRINTF("Requested File: \"");
	PRINTF(name);
	PRINTF("\".\n\r");
	const struct fsdata_file *f;
	Buff[0] = 0;
	strcpy(Buff, "2:/webpage");
	strcat(Buff, name);
	fr = f_open(&fp, Buff, FA_READ);
	if (fr == FR_OK) {
		PRINTF("The file is present with size %d.\n\r", fp.obj.objsize);
		file->len = fp.obj.objsize;
		file->index = 0;
		file->pextension = NULL;
		file->flags = 1;
		return 1;
	}
	else
	{
		PRINTF("Requested file not found.\n\r\n\r");
	}
	return 0;
}

void fs_close_custom(struct fs_file *file) {
	if(f_close(&fp)==FR_OK)
		PRINTF("Requested file closed.\n\r\n\r");
}

int fs_read_custom(struct fs_file *file, char *buffer, int count) {

	int bytes_read;

	if (file) {
		count = (file->index + count > file->len ?file->len - file->index : count);
		//  Read a buffer load
		if (f_read(&fp, buffer, count, (UINT *) &bytes_read) != FR_OK)

		{
			bytes_read = FS_READ_EOF;
		}

		file->index += bytes_read;
	}

	return (bytes_read);
}

