// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <CL/cl.h>
// #include <time.h>
// #include <fstream>
// #include <iostream>

// using namespace std;
// #define NWITEMS 262144

// int convertToString(const char *filename, std::string& s)
// {
//     size_t size;
//     char* str;
//     std::fstream f(filename, (std::fstream::in | std::fstream::binary));
//     if(f.is_open())
//     {
//         size_t fileSize;
//         f.seekg(0, std::fstream::end);
//         size = fileSize = (size_t)f.tellg();
//         f.seekg(0, std::fstream::beg);
//         str = new char[size+1];
//         if(!str)
//         {
//             f.close();
//             return 0;
//         }
//         f.read(str, fileSize);
//         f.close();
//         str[size] = '\0';
//         s = str;
//         delete[] str;
//         return 0;
//     }
//     printf("Error: Failed to open file %s\n", filename);
//     return 1;
// }


// int main(int argc, char* argv[])
// {
//     //在 host 内存中创建三个缓冲区
//     float *buf1 = 0;
//     float *buf2 = 0;
//     float *buf = 0;
//     buf1 = (float *)malloc(NWITEMS * sizeof(float));
//     buf2 = (float *)malloc(NWITEMS * sizeof(float));
//     buf = (float *)malloc(NWITEMS * sizeof(float));
//     // 初始化 buf1 和 buf2 的内容
//     int i;
//     srand((unsigned)time(NULL));
//     for(i = 0; i < NWITEMS; i++)
//         buf1[i] = rand() % 65535;
//     srand((unsigned)time(NULL) +1000);
//     for(i = 0; i < NWITEMS; i++)
//         buf2[i] = rand() % 65535;
//     for(i = 0; i < NWITEMS; i++)
//         buf[i] = buf1[i] + buf2[i];
//     cl_uint status;
//     cl_platform_id platform;
//     status = clGetPlatformIDs( 2, &platform, NULL );
//     cl_device_id device;
//     // 创建 GPU 设备
//     clGetDeviceIDs( platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
//     // 创建 context
//     cl_context context = clCreateContext( NULL,1, &device, NULL, NULL, NULL);
//     // 创建命令队列
//     cl_command_queue queue = clCreateCommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE, NULL);
//     // 创建三个 OpenCL 内存对象,并把 buf1 的内容通过隐式拷贝的方式
//     // 拷贝到 clbuf1, buf2 的内容通过显示拷贝的方式拷贝到 clbuf2
//     cl_mem clbuf1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NWITEMS*sizeof(cl_float), buf1, NULL);
//     cl_mem clbuf2 = clCreateBuffer(context, CL_MEM_READ_ONLY, NWITEMS*sizeof(cl_float), NULL, NULL);
//     status = clEnqueueWriteBuffer(queue, clbuf2, 1, 0, NWITEMS*sizeof(cl_float), buf2, 0, 0, 0);
//     cl_mem buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, NWITEMS * sizeof(cl_float), NULL, NULL);
//     const char * filename = "add.cl";
//     std::string sourceStr;
//     status = convertToString(filename, sourceStr);
//     const char * source = sourceStr.c_str();
//     size_t sourceSize[] = { strlen(source) };
//     cl_program program = clCreateProgramWithSource(context, 1, &source,sourceSize, NULL);
//     // 编译程序对象
//     status = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
//     if(status != 0)
//     {
//         printf("clBuild failed:%d\n", status);
//         char tbuf[0x10000];
//         clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0x10000, tbuf, NULL);
//         printf("\n%s\n", tbuf);
//         return -1;
//     }
//     cl_kernel kernel = clCreateKernel( program, "vecadd", NULL );
//     // 设置 Kernel 参数
//     cl_int clnum = NWITEMS;
//     clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*) &clbuf1);
//     clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*) &clbuf2);
//     clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*) &buffer);
//     // 执行 kernel
//     cl_event ev;
//     size_t global_work_size = NWITEMS;
//     clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_work_size, NULL, 0, NULL, &ev);
//     clFinish(queue);
//     // 数据拷回 host 内存
//     cl_float *ptr;
//     ptr = (cl_float *) clEnqueueMapBuffer(queue, buffer, CL_TRUE, CL_MAP_READ, 0, NWITEMS * sizeof(cl_float), 0, NULL, NULL, NULL);
//     // 结果验证,和 cpu 计算的结果比较
//     if(!memcmp(buf, ptr, NWITEMS)) printf("Verify passed\n");
//     else printf("verify failed");
//     if(buf) free(buf);
//     if(buf1) free(buf1);
//     if(buf2) free(buf2);
//     clReleaseMemObject(clbuf1);
//     clReleaseMemObject(clbuf2);
//     clReleaseMemObject(buffer);
//     clReleaseProgram(program);
//     clReleaseCommandQueue(queue);
//     clReleaseContext(context);
//     return 0;
// }

#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  


#ifdef MAC  
#include <OpenCL/cl.h>  
#else  
#include <CL/cl.h>  
#endif  

int main() {  

    /* Host data structures */  
    cl_platform_id *platforms;  
    //每一个cl_platform_id 结构表示一个在主机上的OpenCL执行平台，就是指电脑中支持OpenCL的硬件，如nvidia显卡，intel CPU和显卡，AMD显卡和CPU等  
    cl_uint num_platforms;  
    cl_int i, err, platform_index = -1;  

    /* Extension data */  
    char* ext_data;                           
    size_t ext_size;     
    const char icd_ext[] = "cl_khr_icd";  

    //要使platform工作，需要两个步骤。1 需要为cl_platform_id结构分配内存空间。2 需要调用clGetPlatformIDs初始化这些数据结构。一般还需要步骤0：询问主机上有多少platforms  

    /* Find number of platforms */  
    //返回值如果为-1就说明调用函数失败，如果为0标明成功  
    //第二个参数为NULL代表要咨询主机上有多少个platform，并使用num_platforms取得实际flatform数量。  
    //第一个参数为1，代表我们需要取最多1个platform。可以改为任意大如：INT_MAX整数最大值。但是据说0，否则会报错，实际测试好像不会报错。下面是步骤0：询问主机有多少platforms  
    err = clGetPlatformIDs(5, NULL, &num_platforms);          
    if(err < 0) {          
        perror("Couldn't find any platforms.");           
        exit(1);                              
    }                                     

    printf("I have platforms: %d\n", num_platforms); //本人计算机上显示为2，有intel和nvidia两个平台  

    /* Access all installed platforms */  
    //步骤1 创建cl_platform_id，并分配空间  
    platforms = (cl_platform_id*)                     
        malloc(sizeof(cl_platform_id) * num_platforms);   
    //步骤2 第二个参数用指针platforms存储platform  
    clGetPlatformIDs(num_platforms, platforms, NULL);         

    /* Find extensions of all platforms */  
    //获取额外的平台信息。上面已经取得了平台id了，那么就可以进一步获取更加详细的信息了。  
    //一个for循环获取所有的主机上的platforms信息  
    for(i=0; i<num_platforms; i++)   
    {  
        /* Find size of extension data */  
        //也是和前面一样，先设置第三和第四个参数为0和NULL，然后就可以用第五个参数ext_size获取额外信息的长度了。  
        err = clGetPlatformInfo(platforms[i],             
            CL_PLATFORM_EXTENSIONS, 0, NULL, &ext_size);      
        if(err < 0)   
        {  
            perror("Couldn't read extension data.");              
            exit(1);  
        }     

        printf("The size of extension data is: %d\n", (int)ext_size);//我的计算机显示224.  

        /* Access extension data */    
        //这里的ext_data相当于一个缓存，存储相关信息。  
        ext_data = (char*)malloc(ext_size);   
        //这个函数就是获取相关信息的函数，第二个参数指明了需要什么样的信息，如这里的CL_PLATFORM_EXTENSIONS表示是opencl支持的扩展功能信息。我计算机输出一大串，机器比较新（专门为了学图形学而购置的电脑），支持的东西比较多。  
        clGetPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS,       
            ext_size, ext_data, NULL);                
        printf("Platform %d supports extensions: %s\n", i, ext_data);  

        //这里是输出生产商的名字，比如我显卡信息是：NVIDIA CUDA  
        char *name = (char*)malloc(ext_size);  
        clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME,     
            ext_size, name, NULL);                
        printf("Platform %d name: %s\n", i, name);  

        //这里是供应商信息，我显卡信息：NVIDIA Corporation  
        char *vendor = (char*)malloc(ext_size);  
        clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR,       
            ext_size, vendor, NULL);                  
        printf("Platform %d vendor: %s\n", i, vendor);  

        //最高支持的OpenCL版本，本机显示：OpenCL1.1 CUDA 4.2.1  
        char *version = (char*)malloc(ext_size);  
        clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION,      
            ext_size, version, NULL);                 
        printf("Platform %d version: %s\n", i, version);  

        //这个只有两个值：full profile 和 embeded profile  
        char *profile = (char*)malloc(ext_size);  
        clGetPlatformInfo(platforms[i], CL_PLATFORM_PROFILE,      
            ext_size, profile, NULL);                 
        printf("Platform %d full profile or embeded profile?: %s\n", i, profile);  

        /* Look for ICD extension */     
        //如果支持ICD这一扩展功能的platform，输出显示，本机的Intel和Nvidia都支持这一扩展功能  
        if(strstr(ext_data, icd_ext) != NULL)   
            platform_index = i;  
        //std::cout<<"Platform_index = "<<platform_index<<std::endl;  
        printf("Platform_index is: %d\n", platform_index);  
        /* Display whether ICD extension is supported */  
        if(platform_index > -1)  
            printf("Platform %d supports the %s extension.\n",   
            platform_index, icd_ext);  


        //释放空间  
        free(ext_data);  
        free(name);  
        free(vendor);  
        free(version);  
        free(profile);  
    }  

    if(platform_index <= -1)  
        printf("No platforms support the %s extension.\n", icd_ext);  

    /* Deallocate resources */  
    free(platforms);  
    return 0;  
}  