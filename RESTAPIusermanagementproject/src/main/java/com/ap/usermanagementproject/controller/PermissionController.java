package com.ap.usermanagementproject.controller;

import com.ap.usermanagementproject.entities.Permission;
import com.ap.usermanagementproject.repositories.PermissionRepository;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController()
@RequestMapping("/permission")
public class PermissionController extends BaseController<Permission, PermissionRepository>{}