package com.ap.usermanagementproject.controller;

import com.ap.usermanagementproject.entities.GroupEntity;
import com.ap.usermanagementproject.repositories.GroupRepository;
import com.ap.usermanagementproject.services.GroupRService;

import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/group")
public class GroupController extends BaseGetController<GroupEntity, GroupRepository, GroupRService>{}