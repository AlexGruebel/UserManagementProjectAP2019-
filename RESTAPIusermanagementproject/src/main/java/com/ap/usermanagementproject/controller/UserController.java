package com.ap.usermanagementproject.controller;

import com.ap.usermanagementproject.entities.ResponseBodyMultipleItems;
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
    public ResponseBodyMultipleItems<User> getuser(@RequestParam(required = false, defaultValue = "1") Integer page
                                                  ,@RequestParam(required = false, defaultValue = "100") Short limit) 
    {        
        ResponseBodyMultipleItems<User> body = new ResponseBodyMultipleItems<User>(page, limit);
        body.fillBodyWithRepository(userRepository);
        return body;
    }
}