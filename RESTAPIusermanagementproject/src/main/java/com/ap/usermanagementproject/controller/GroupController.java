package com.ap.usermanagementproject.controller;

import com.ap.usermanagementproject.entities.ResponseBodyMultipleItems;
import com.ap.usermanagementproject.entities.Group;
import com.ap.usermanagementproject.repositories.GroupRepository;

import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/group")
public class GroupController extends BaseGetController<Group, GroupRepository>{}