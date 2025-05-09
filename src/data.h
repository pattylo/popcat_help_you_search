#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <vector>
#include <string>


// define data structure
struct Command {
    std::string keyword;
    std::vector<std::string> commands;
};

struct Subcategory{
    std::string name;
    std::vector<std::string> keywords;
    std::vector<std::string> commands;
};

struct category{
    std::string name;
    std::vector<std::string> keywords;
    std::vector<Subcategory> subcate;
};

// git
const Subcategory subcate_git_user = {
    "user", 
    {"user", "config", "USER", "CONFIG", "name", "NAME", "email", "EMAIL"}, 
    {
        "git config --global user.name {name}",
        "git config --global user.email {email}",
        "git config --global --unset user.name",
        "git config --global --unset user.email"
    }
};
const Subcategory subcate_git_repo_init = {
    "repo_init", 
    {"init", "INIT"}, 
    {
        "git init",
        "git remote add origin https://github.com/{username}/{lala}.git",
        "git branch -M main",
        "git add .",
        "git commit -m \"initial commit\"",
        "git push -u origin main"
    }
};
const Subcategory subcate_git_repo_commit = {
    "repo_commit", 
    {"commit", "COMMIT", "push", "PUSH"}, 
    {
        "git reset --hard # discard changes",
        "git status",
        "git add .",
        "git commit -a || git commit -m \"{message}\" # (quit vim: esc + \":wq\")",
        "git push -u origin main"
    }
};
const Subcategory subcate_git_repo_merge = {
    "repo_merge", 
    {"merge", "MERGE", "remote", "REMOTE", "pull", "PULL"}, 
    {
        "git remote set-url origin https://github.com/pattylo/gan.git  # ||",
        "git remote add origin https://github.com/pattylo/gan.git",
        "git remote -v",
        "\n",
        "git pull origin main --allow-unrelated-histories",
        "git pull = git fetch + git merge",
        "\n",
        "git config pull.rebase false # if neccessary # resolve conflict if needed",
        "git push -u origin main",
        "# Note that do set the default main (master in legacy)",
        "git remote set-head origin {branch-name} #",
    }
};
const Subcategory subcate_git_repo_branch_tag = {
    "branch_rag", 
    {"branch", "BRANCH", "tag", "TAG"}, 
    {
        "git branch {new branch-name}",
        "git checkout -b {new branch-name} {off which branch}",
        "\n",
        "git branch # check all branches",
        "git switch {branch-name} || git checkout {branch-name}",
        "git push -u origin {branch-name}"
    }
};

const category command_git = {
    "git", 
    {"git", "GIT"},
    {
        subcate_git_user,
        subcate_git_repo_init,
        subcate_git_repo_commit,
        subcate_git_repo_merge,
        subcate_git_repo_branch_tag
    }
};

// docker
const Subcategory subcate_docker_image = {
    "image", 
    {"image", "IMAGE", "pull", "PULL", "run", "RUN"}, 
    {
        "docker image pull {image_name} # pull an image",
        "docker run -blah_blah {image_name} # run an image and create a container",
        "docker image ls # list all image",
        "docker rmi {image_name}"
    }
};

const Subcategory subcate_docker_commit = {
    "commit", 
    {"commit", "COMMIT", "push", "PUSH"}, 
    {
        "docker commit {container_name} {new_image_name}",
        "# create an image after you modify a container # this could become your new template",
        "\n",
        "docker login",
        "docker logout",
        "docker tag {container_name} {username}/{remote_image_name}",
        "docker push {username}/{remote_image_name}"
    }
};

const Subcategory subcate_docker_container = {
    "container", 
    {"container", "CONTAINER", "start", "START", "attach", "ATTACH"}, 
    {
        "docker exec -it {container_name} /bin/bash", 
        "# attach to the same container without echoing the same commandline",
        "\n",
        "docker start {container_name} # start container",
        "docker attach {container_name} # attach to a container, namely, get inside the container",
        "ctrl + p then ctrl + q to detach from docker",
        "exit # exit container",
        "docker rm {container_name}"
    }
};

const Subcategory subcate_docker_space = {
    "space", 
    {"remove", "REMOVE", "prune", "PRUNE"}, 
    {
        "docker system prune --all",
    }
};

const category command_docker = {
    "docker", 
    {"docker", "DOCKER"},
    {
        subcate_docker_image,
        subcate_docker_commit,
        subcate_docker_container,
        subcate_docker_space
    }
};

// remote
const Subcategory subcate_remote_setup = {
    "setup", 
    {"setup", "install", "INSTALL", "SETUP"}, 
    {
        "sudo apt-get install openssh-server",
    }
};

const Subcategory subcate_remote_ssh = {
    "transmit", 
    { "transmit", "TRANSMIT"}, 
    {
        "ssh {username}@{ip_addr} -p {port_number}",
        "ssh patty@0.tcp.ap.ngrok.io -p12905",
        "\n",
        "zip -r {filename}.zip {filename}",
        "sudo scp -P {port_number} {file_name} {username}@{IP_ADDR}:{directory_localtion}",
        "sudo scp -P {port_number} {file_name} {username}@0.tcp.jp.ngrok.io:{directory_localtion}",
        "\n",
        "nano /etc/ssh/sshd_config",
        "PermitRootLogin Yes",
        "Port 6666"
    }
};

const Subcategory subcate_remote_ngrok = {
    "ngrok", 
    { "ngrok", "NGROK"}, 
    {
        "# install",
        "curl -s https://ngrok-agent.s3.amazonaws.com/ngrok.asc \\",
        " | sudo tee /etc/apt/trusted.gpg.d/ngrok.asc >/dev/null && \\", 
        " echo \"deb https://ngrok-agent.s3.amazonaws.com buster main\" \\",
        " | sudo tee /etc/apt/sources.list.d/ngrok.list && \\",
        " sudo apt update && sudo apt install ngrok",
        "\n",
        "# post-install",
        "ngrok config add-authtoken <token>",
        "\n",
        "# on ngrok server create ngrok.sh",
        "cd /usr/local/bin",
        "./ngrok tcp 22 # for ssh purpose"
    }
};

const category command_remote = {
    "ssh", 
    {"ssh", "SSH"},
    {
        subcate_remote_setup,
        subcate_remote_ssh,
        subcate_remote_ngrok,
    }
};

// vicon
const Subcategory subcate_vicon_install = {
    "install", 
    { "install", "INSTALL"}, 
    {
        "sudo apt update",
        "sudo apt-get install ros-noetic-vrpn ros-noetic-vrpn-client-ros",
    }
};

const Subcategory subcate_vicon_remap = {
    "remap", 
    { "remap", "REMAP"}, 
    {
        "<remap from=\"/vrpn_client_node/{your_object_name}/pose\" to=\"/mavros/vision_pose/pose\" />",
    }
};

const Subcategory subcate_vicon_launch = {
    "launch", 
    { "launch", "LAUNCH", "roslaunch", "ROSLAUNCH"}, 
    {
        "<launch>",
        "\n",
        "   <arg name=\"vicon_server\" default=\"192.168.10.1\"/>",
        "\n",
        "       <node pkg=\"vrpn_client_ros\" type=\"vrpn_client_node\" name=\"vrpn_client_node\" output=\"screen\">",
        "           <rosparam subst_value=\"true\">",
        "               server: $(arg vicon_server)",
        "               port: 3883",
        "\n",
        "               update_frequency: 100.0",
        "               frame_id: world",
        "\n",
        "               # Use the VRPN server's time, or the client's ROS time.",
        "               use_server_time: false",
        "               broadcast_tf: true",
        "\n",
        "               # Must either specify refresh frequency > 0.0, or a list of trackers to create",
        "               refresh_tracker_frequency: 1.0",
        "               #trackers:",
        "               #- FirstTracker",
        "               #- SecondTracker",
        "           </rosparam>",
        "\n",
        "       <remap from=\"/vrpn_client_node/your_object_name/pose\" to=\"/mavros/vision_pose/pose\" />",
        "       </node>"
        "\n",
        "</launch>",
    }
};

const Subcategory subcate_vicon_multi = {
    "multi", 
    { "multi", "MULTI"}, 
    {
        "# master_multi.sh",
        "export ROS_HOSTNAME=192.168.{MASTER_IP}",
        "export ROS_MASTER_URI=http://192.168.{MASTER_IP}:11311",
        "export ROS_IP=192.168.{MASTER_IP}",
        "\n",
        "# slave_multi.sh",
        "export ROS_HOSTNAME=192.168.{SLAVE_IP}",
        "export ROS_MASTER_URI=http://192.168.{MASTER_IP}:11311",
        "export ROS_IP=192.168.{SLAVE_IP}",
    }
};

const category command_vicon = {
    "vicon", 
    {"vicon", "VICON"},
    {
        subcate_vicon_install,
        subcate_vicon_remap,
        subcate_vicon_launch,
        subcate_vicon_multi
    }
};

// mavros 
const Subcategory subcate_mavros_install = {
    "install", 
    { "install", "INSTALL"}, 
    {
        "# ubuntu 18.04",
        "sudo apt-get install ros-melodic-mavros ros-melodic-mavros-extras ros-melodic-mavros-msgs",
        "\n",
        "# ubuntu 20.04",
        "sudo apt-get install ros-noetic-mavros ros-noetic-mavros-extras ros-noetic-mavros-msgs"
    }
};

const Subcategory subcate_mavros_launch = {
    "launch", 
    { "launch", "LAUNCH"}, 
    {
        "<launch>",
        "    <!-- example launch script for PX4 based FCU's -->",
        "",
        "    <!-- launch MAVLINK in ROS -->",
        "    <arg name=\"fcu_url\" default=\"/dev/ttyUSB0:921600\" />",
        "    <!-- ",
        "        when using USB serial (w/ onboard computer)",
        "        - note that from time to time it might be ",
        "          /dev/ttyACM0 (check it through \"ls /dev/tty + tab\")",
        "        - note that baudrate \"921600\" varies from time to time,",
        "          it depends on your setting in GGC            ",
        "    -->",
        "",
        "    <!-- <arg name=\"fcu_url\" default=\"tcp://{IP_ADDRRESS}:5760\" /> -->",
        "    <!-- when using WIFI-module (w/o onboard computer) -->",
        "",
        "    <!-- <arg name=\"fcu_url\" default=\"udp://:14540@127.0.0.1:14557\" /> -->",
        "    <!-- during Gazebo SITL simulation -->",
        "",
        "    <!-- QGC broadcast -->",
        "    <arg name=\"gcs_url\" default=\"udp-b://@\" /> ",
        "    <!-- boardcast to all local network -->",
        "",
        "    <!-- <arg name=\"gcs_url\" default=\"udp://:14560@{IP_ADDRRESS}:14550\" /> -->",
        "    <!-- broadcast to specific IP -->",
        "",
        "    <!-- <arg name=\"gcs_url\" default=\"udp://:14560@127.0.0.1:14550\" /> -->",
        "    <!-- during Gazebo SITL simulation -->",
        "",
        "",
        "    <arg name=\"tgt_system\" default=\"1\" />",
        "    <arg name=\"tgt_component\" default=\"1\" />",
        "    <arg name=\"log_output\" default=\"screen\" />",
        "    <arg name=\"fcu_protocol\" default=\"v2.0\" />",
        "    <arg name=\"respawn_mavros\" default=\"false\" />",
        "",
        "    <include file=\"$(find mavros)/launch/node.launch\">",
        "        <arg name=\"pluginlists_yaml\" value=\"$(find mavros)/launch/px4_pluginlists.yaml\" />",
        "        <arg name=\"config_yaml\" value=\"$(find mavros)/launch/px4_config.yaml\" />",
        "",
        "        <arg name=\"fcu_url\" value=\"$(arg fcu_url)\" />",
        "        <arg name=\"gcs_url\" value=\"$(arg gcs_url)\" />",
        "        <arg name=\"tgt_system\" value=\"$(arg tgt_system)\" />",
        "        <arg name=\"tgt_component\" value=\"$(arg tgt_component)\" />",
        "        <arg name=\"log_output\" value=\"$(arg log_output)\" />",
        "        <arg name=\"fcu_protocol\" value=\"$(arg fcu_protocol)\" />",
        "        <arg name=\"respawn_mavros\" default=\"$(arg respawn_mavros)\" />",
        "    </include>",
        "</launch>"
    }
};

const Subcategory subcate_mavros_fcu = {
    "fcu", 
    { "fcu", "FCU"}, 
    {
        "<!--when using USB serial (w/ onboard computer)-->",
        "<arg name=\"fcu_url\" default=\"/dev/ttyUSB0:921600\" />",
        "\n",
        "<!-- when using WIFI-module (w/o onboard computer) -->",
        "<arg name=\"fcu_url\" default=\"tcp://{IP_ADDRRESS}:5760\" />",
        "\n",
        "<!-- during Gazebo SITL simulation -->",
        "<arg name=\"fcu_url\" default=\"udp://:14540@127.0.0.1:14557\" />",
        "\n",
    }
};

const Subcategory subcate_mavros_gcs = {
    "gcs", 
    { "gcs", "GCS"}, 
    {
        "<!-- boardcast to all local network -->",
        "<arg name=\"gcs_url\" default=\"udp-b://@\" />",
        "\n",
        "<!-- broadcast to specific IP -->",
        "<arg name=\"gcs_url\" default=\"udp://:14560@{IP_ADDRRESS}:14550\" />",
        "\n",
        "<!-- during Gazebo SITL simulation -->",
        "<arg name=\"gcs_url\" default=\"udp://:14560@127.0.0.1:14550\" />",
        "\n",
    }
};

const category command_mavros = {
    "mavros", 
    {"mavros", "MAVROS"},
    {
        subcate_mavros_install,
        subcate_mavros_launch,
        subcate_mavros_fcu,
        subcate_mavros_gcs
    }
};

// latex
const Subcategory subcate_latex_install = {
    "install",
    {"install", "INSTALL"},
    {
        "# mac",
        "brew install --cask mactex-no-gui",
        "\n",
        "# ubuntu",
        "sudo apt install texlive-latex-extra"
    }
};

const category command_latex = {
    "latex",
    {"LATEX", "latex"},
    {
        subcate_latex_install
    }
};

const Subcategory subcate_conda_env = {
    "env",
    {"env", "ENV"},
    {
        "conda env list",
        "conda create --name {name} python=3.5 ",
        "conda activate {name}",
        "conda deactivate",
        "conda install --file {setup}.txt"
        "conda env remove --name {name}"
    }
};

const category command_conda = {
    "latex",
    {"LATEX", "latex"},
    {
        subcate_conda_env
    }
};


// all database
const std::vector<category> database = {
    command_git,
    command_docker, 
    command_remote, 
    command_vicon,
    command_mavros,
    command_latex,
    command_conda
};

#endif