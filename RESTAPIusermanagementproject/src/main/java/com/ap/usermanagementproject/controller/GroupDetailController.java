package com.ap.usermanagementproject.controller;

import com.ap.usermanagementproject.entities.GroupDetail;
import com.ap.usermanagementproject.repositories.GroupDetailRepository;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController()
@RequestMapping("/groupdetail")
public class GroupDetailController extends BaseController<GroupDetail, GroupDetailRepository>{}