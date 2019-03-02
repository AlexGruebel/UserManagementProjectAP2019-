package com.ap.usermanagementproject.controller;

import com.ap.usermanagementproject.entities.GroupDetailEntity;
import com.ap.usermanagementproject.repositories.GroupDetailRepository;
import com.ap.usermanagementproject.services.GroupDetailCRUDService;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController()
@RequestMapping("/api/groupdetail")
public class GroupDetailController extends BaseController<GroupDetailEntity, GroupDetailRepository, GroupDetailCRUDService>{}