#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>

// Define video parameters
#define WIDTH 1920
#define HEIGHT 1080
#define FRAME_SIZE WIDTH * HEIGHT

#define IN_HEIGHT 1920
#define IN_WIDTH 1080
#define OUT_WIDTH 1280
#define OUT_HEIGHT 720

#define FRAMEBUFFER_DEVICE "/dev/fb0"
// #define PATH "../../record.raw"
#define PATH "../../video1.raw"

int main() {
    int fbfd;
    unsigned char *fb, *p;
    struct fb_var_screeninfo vinfo;
    int fb_width, tmp; 
    FILE *videoFile;

    fbfd = open(FRAMEBUFFER_DEVICE, O_RDWR);
    ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo);
    fb = (unsigned char *)mmap(0, vinfo.yres_virtual * vinfo.xres_virtual * vinfo.bits_per_pixel / 8, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);


    // Buffer for storing YUV frame data
    uint8_t *in_frame = (uint8_t *)malloc(FRAME_SIZE);
    if (!in_frame) {
        fprintf(stderr, "Failed to allocate memory.\n");
        fclose(videoFile);
        return 1;
    }

    while(1){
        // Open raw video file
        videoFile = fopen(PATH, "rb");
        if (!videoFile) {
            fprintf(stderr, "Failed to open video file.\n");
            return 1;
        }
        while(fread(in_frame, 1, FRAME_SIZE, videoFile) == FRAME_SIZE){
            int fb_width = vinfo.xres_virtual;
            for(int i=0; i<HEIGHT; i++){
                for(int j=0; j<WIDTH; j++){
                    p = fb + 4*(fb_width * i + j);
                    p[0] = in_frame[i * WIDTH + j];
                    p[1] = in_frame[i * WIDTH + j];
                    p[2] = in_frame[i * WIDTH + j];
                }
            }
            usleep(30000);
        }

        fclose(videoFile);
    }

    fclose(videoFile);
    free(in_frame);

    return 0;
}
