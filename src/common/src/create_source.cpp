#include "common/create_source.hpp"
#include "config/config.hpp"
#include "deepstream_sources.h"
#include "spdlog/spdlog.h"

NvDsSourceType GetSourceType(std::string type){
  if (type == "rtsp") return NV_DS_SOURCE_RTSP;
  else if (type == "uri") return NV_DS_SOURCE_URI;
  else if (type =="camera_v4l2") return NV_DS_SOURCE_CAMERA_V4L2;
  else if (type == "multiple") return NV_DS_SOURCE_URI_MULTIPLE;
  else if (type == "cam_sci") return NV_DS_SOURCE_CAMERA_CSI;
  else if (type == "autdio_wav") return NV_DS_SOURCE_AUDIO_WAV;
  else if (type == "audio_uri") return NV_DS_SOURCE_AUDIO_URI;
  else if (type == "alsa_src") return NV_DS_SOURCE_ALSA_SRC;
  else{
    spdlog::error("Does not support {}. Exiting...", type);
    exit(0);
    }
}



GstElement* Source::Create(){
  // TODO: Have to check whether key is exiting or not before get value!!!!!!!!!!!!
  // This code so dirty, you should refacetor
  auto all_configs = Config::Instance()->GetAllConfig();
  auto sources = all_configs["source"]["sources"];

  NvDsSourceConfig *nvds_source_configs = new NvDsSourceConfig[1024];
  NvDsSrcParentBin *nvds_parent_bin = new NvDsSrcParentBin();

  int cudadec_mem_type = all_configs["common"]["cudadec_mem_type"];
  int nvbuf_memory_type = all_configs["common"]["nvbuf_memory_type"];

  int number_sources = sources.size();

  for (int i = 0; i < number_sources; i++){
    auto source_config = sources[i];
    
    NvDsSourceConfig *src_bin_config = new NvDsSourceConfig();
    auto input_type = GetSourceType(source_config["type"]);
    auto enable = source_config["enable"];
    std::string uri = (std::string)source_config["uri"];
    int drop_frame_interval = source_config["drop_frame_interval"];
    int gpu_id = source_config["gpu_id"];

    src_bin_config->type = input_type;
    src_bin_config->enable = enable;
    src_bin_config->uri = strdup(uri.c_str());
    src_bin_config->gpu_id = gpu_id;
    src_bin_config->drop_frame_interval = drop_frame_interval;
    src_bin_config->cuda_memory_type = cudadec_mem_type;

    nvds_source_configs[i] = *src_bin_config;
  }
  create_multi_source_bin(number_sources, nvds_source_configs, nvds_parent_bin);

  auto streamuxer_config = all_configs["source"]["streamuxer"];
  int width = streamuxer_config["width"];
  int height = streamuxer_config["height"];
  int batched_push_timeout = streamuxer_config["batched_push_timeout"];
  int gpu_id = streamuxer_config["gpu_id"];
  int enable_padding = streamuxer_config["enable_padding"];

  g_object_set (G_OBJECT (nvds_parent_bin->streammux), "batch-size", number_sources, NULL);
  g_object_set (G_OBJECT (nvds_parent_bin->streammux), "width", width, NULL);
  g_object_set (G_OBJECT (nvds_parent_bin->streammux), "height",height, NULL);
  g_object_set (G_OBJECT (nvds_parent_bin->streammux), "batched-push-timeout", batched_push_timeout, NULL);
  g_object_set (G_OBJECT (nvds_parent_bin->streammux), "gpu-id", gpu_id, NULL);
  g_object_set (G_OBJECT (nvds_parent_bin->streammux), "enable-padding", enable_padding, NULL);
  g_object_set (G_OBJECT (nvds_parent_bin->streammux), "nvbuf-memory-type", nvbuf_memory_type, NULL);

  return nvds_parent_bin->bin;
}