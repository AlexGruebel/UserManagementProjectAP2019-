package com.ap.usermanagementproject.controller;

import com.ap.usermanagementproject.entities.UserDetailEntity;
import com.ap.usermanagementproject.entities.UserDetailWithPWEntity;
import com.ap.usermanagementproject.repositories.UserDetailRepository;
import com.ap.usermanagementproject.services.UserDetailCRUDService;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/api/userdetail")
public class UserDetailController extends ExtBaseController<UserDetailEntity
                                                        ,UserDetailWithPWEntity
                                                        ,UserDetailRepository
                                                        ,UserDetailCRUDService>
{
    @GetMapping("/isAdmin/{username}")
    public boolean get(@PathVariable String username) {
        return super.getService().isAdmin(username);
    }

}