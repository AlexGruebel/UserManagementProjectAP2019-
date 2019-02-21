package com.ap.usermanagementproject.controller;

import com.ap.usermanagementproject.entities.Group;
import com.ap.usermanagementproject.repositories.GroupRepository;

import org.springframework.web.bind.annotation.*;

@RestController()
@RequestMapping("/groupdetail")
public class GroupDetailController extends BaseController<Group, GroupRepository>{}