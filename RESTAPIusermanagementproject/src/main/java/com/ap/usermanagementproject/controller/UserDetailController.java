package com.ap.usermanagementproject.controller;

import com.ap.usermanagementproject.entities.ResponseBodyMultipleItems;
import com.ap.usermanagementproject.entities.UserDetail;
import com.ap.usermanagementproject.repositories.UserDetailRepository;

import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/")
public class UserDetailController{

    private UserDetailRepository userDetailRepository;

    public UserDetailController(UserDetailRepository userDetailRepository){
        this.userDetailRepository = userDetailRepository;
    }


    @GetMapping(value="/userdetail")
    public ResponseBodyMultipleItems<UserDetail> getAllUserDetails(@RequestParam(required = false, defaultValue = "1") Integer page
                                                                  ,@RequestParam(required = false, defaultValue = "100") Short limit) 
    {
        ResponseBodyMultipleItems<UserDetail> body = new ResponseBodyMultipleItems<UserDetail>(page, limit);
        body.fillBodyWithRepository(userDetailRepository);
        return body;
    }
    
    @PostMapping(value="/userdetail")
    public UserDetail postUser(@RequestBody UserDetail entity) {
        this.userDetailRepository.save(entity);
        return entity;
    }
    
    @PutMapping(value="/userdetail/{id}")
    public UserDetail putUser(@PathVariable int id, @RequestBody UserDetail entity) {
        this.userDetailRepository.save(entity);
        return entity;
    }

    @DeleteMapping
    public void deleteUser(@PathVariable int id){
        this.userDetailRepository.deleteById(id);
    }
}