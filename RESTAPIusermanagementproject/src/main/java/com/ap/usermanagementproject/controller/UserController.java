package com.ap.usermanagementproject.controller;

import java.util.ArrayList;
import java.util.List;

import com.ap.usermanagementproject.entities.User;
import com.ap.usermanagementproject.repositories.UserRepository;

import org.springframework.web.bind.annotation.*;

@RestController
public class UserController{

    private UserRepository userRepository;

    public UserController(UserRepository userRepository){
        this.userRepository = userRepository;
    }

    @GetMapping("/user")
    public List<User> getuser(){        
        List<User> users = new ArrayList<User>();
        this.userRepository.findAll().forEach(user -> users.add(user));
        return users;
    }
}