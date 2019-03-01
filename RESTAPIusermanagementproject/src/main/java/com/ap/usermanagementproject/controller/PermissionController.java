package com.ap.usermanagementproject.controller;

import com.ap.usermanagementproject.entities.Permission;
import com.ap.usermanagementproject.repositories.PermissionRepository;
import com.ap.usermanagementproject.services.PermissionCRUDService;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController()
@RequestMapping("/api/permission")
public class PermissionController extends BaseController<Permission, PermissionRepository, PermissionCRUDService>{}