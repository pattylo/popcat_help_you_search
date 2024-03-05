#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <vector>
#include <string>


// Define data structure
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
    {"user", "config", "USER", "CONFIG"}, 
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
        "docker commit {container_name} {new_image_name} # create an image after you modify a container # this could become your new template",
        "docker login",
        "docker logout",
        "docker tag {container_name} {username}/{remote_image_name}",
        "docker push {username}/{remote_image_name}"
    }
};

const Subcategory subcate_docker_container = {
    "container", 
    {"container", "CONTAINER", "start", "attach"}, 
    {
        "docker exec -it {container_name} /bin/bash # attach to the same container without echoing the same commandline",
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

// all database
const std::vector<category> database = {command_git,command_docker};



#endif