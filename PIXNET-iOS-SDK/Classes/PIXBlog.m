//
//  PIXBlog.m
//  PIXNET-iOS-SDK
//
//  Created by Dolphin Su on 3/14/14.
//  Copyright (c) 2014 PIXNET. All rights reserved.
//

#import "PIXBlog.h"
#import "PIXAPIHandler.h"
#import "NSObject+PIXCategory.h"
#import "NSError+PIXCategory.h"

@implementation PIXBlog

#pragma mark - Blog information
- (void)getBlogInformationWithUserName:(NSString *)userName
                          completion:(PIXHandlerCompletion)completion{
    //檢查進來的參數
    if (userName == nil) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing User Name"]);
        return;
    }
    [[PIXAPIHandler new] callAPI:@"blog"
                      parameters:@{@"user": userName}
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
        //檢查出去的參數
        if (succeed) {
            [self succeedHandleWithData:result completion:completion];
        } else {
            completion(NO, nil, errorMessage);
        }
    }];
}

#pragma mark - Blog Categories
- (void)getBlogCategoriesWithUserName:(NSString *)userName
                             password:(NSString *)passwd
                           completion:(PIXHandlerCompletion)completion{
    //檢查進來的參數
    if (userName == nil || userName.length==0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing User Name"]);
        return;
    }
    NSMutableDictionary *params = [NSMutableDictionary new];
    params[@"user"] = userName;
    
    if (passwd != nil) {
        params[@"blog_password"] = passwd;
    }
    [[PIXAPIHandler new] callAPI:@"blog/categories"
                      parameters:params
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
        if (succeed) {
            [self succeedHandleWithData:result completion:completion];
        } else {
            completion(NO, nil, errorMessage);
        }
    }];
}
#pragma mark Categories need access token
- (void)createBlogCategoriesWithName:(NSString *)name
                                type:(PIXBlogCategoryType)type
                         description:(NSString *)description
                        siteCategory:(NSString *)siteCateID
                          completion:(PIXHandlerCompletion)completion{
    
    if (!name || name == nil || name.length == 0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing Category Name"]);
        return;
    }

    NSMutableDictionary *params = [NSMutableDictionary new];
    params[@"name"] = name;
    
    if (type == PIXBlogCategoryTypeCategory) {
        params[@"type"] = @"category";
        params[@"site_category_done"] = @"1";
        params[@"site_category_id"] = siteCateID;
    
    }else if (type == PIXBlogCategoryTypeFolder){
        params[@"type"] = @"folder";
    }
    
    if (description || description != nil || description.length != 0) {
        params[@"description"] = description;
    }
    
    [[PIXAPIHandler new] callAPI:@"blog/categories"
                      httpMethod:@"POST"
                      shouldAuth:YES
                      parameters:params
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
        if (succeed) {
            [self succeedHandleWithData:result completion:completion];
        } else {
            completion(NO, nil, errorMessage);
        }
    }];
    
}

- (void)updateBlogCategoryFromID:(NSString *)categoryID
                           newName:(NSString *)newName
                              type:(PIXBlogCategoryType)type
                       description:(NSString *)description
                        completion:(PIXHandlerCompletion)completion{
    if (categoryID==nil || categoryID.length==0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"categoryID 參數有誤"]);
    }
    if (newName == nil || newName.length == 0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing New Name"]);
    }
    
    NSMutableDictionary *params = [NSMutableDictionary new];
    params[@"name"] = newName;
    switch (type) {
        case PIXBlogCategoryTypeCategory:
            params[@"type"] = @"category";
            break;
        case PIXBlogCategoryTypeFolder:
            params[@"type"] = @"folder";
            break;
        default:
            break;
    }

    if (description != nil && description.length > 0) {
        params[@"description"] = description;
    }
    
    [[PIXAPIHandler new] callAPI:[NSString stringWithFormat:@"blog/categories/%@", categoryID]
                      httpMethod:@"POST"
                      shouldAuth:YES
                      parameters:params
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
        if (succeed) {
            [self succeedHandleWithData:result completion:completion];
        } else {
            completion(NO, nil, errorMessage);
        }
    }];
    
}

- (void)deleteBlogCategoriesByID:(NSString *)categoriesID
                            type:(PIXBlogCategoryType)type
                      completion:(PIXHandlerCompletion)completion{
    if (!categoriesID || categoriesID == nil || categoriesID.length == 0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing Category/Folder ID"]);
    }
    
    NSMutableDictionary *params = [NSMutableDictionary new];
    
    if (type == PIXBlogCategoryTypeCategory) {
        params[@"type"] = @"category";
    }else{
        params[@"type"] = @"folder";
    }
    
    params[@"_method"] = @"delete";
    
    [[PIXAPIHandler new] callAPI:[NSString stringWithFormat:@"blog/categories/%@", categoriesID]
                      httpMethod:@"POST"
                      shouldAuth:YES
                      parameters:params
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
                   if (succeed) {
                       [self succeedHandleWithData:result completion:completion];
                   } else {
                       completion(NO, nil, errorMessage);
                   }
               }];

}

- (void)sortBlogCategoriesTo:(NSArray *)categoriesIDArray
                  completion:(PIXHandlerCompletion)completion{
    NSString *idsString = [categoriesIDArray componentsJoinedByString:@"-"];
    NSDictionary *params = @{@"ids": idsString};

    [[PIXAPIHandler new] callAPI:@"blog/categories/position"
                      httpMethod:@"POST"
                      shouldAuth:YES
                      parameters:params
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
                   if (succeed) {
                       [self succeedHandleWithData:result completion:completion];
                   } else {
                       completion(NO, nil, errorMessage);
                   }
               }];
}


#pragma mark - Blog Articles
- (void)getBlogAllArticlesWithUserName:(NSString *)userName
                              password:(NSString *)passwd
                                  page:(NSUInteger)page
                               perpage:(NSUInteger)articlePerPage
                        userCategories:(NSArray *)userCategories
                                status:(PIXArticleStatus)status
                                 isTop:(BOOL)isTop
                              trimUser:(BOOL)trimUser
                            completion:(PIXHandlerCompletion)completion{
    //檢查進來的參數
    if (userName == nil) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing User Name"]);
        return;
    }
    NSMutableDictionary *params = [NSMutableDictionary new];
    params[@"user"] = userName;
    
    if (passwd && passwd.length>0) {
        params[@"blog_password"] = passwd;
    }
    if (page <= 0) {
        params[@"page"] = @"1";
    } else {
        params[@"page"] = [NSString stringWithFormat:@"%li", page];
    }
    if (articlePerPage <= 0) {
        params[@"per_page"] = @"20";
    } else {
        params[@"per_page"] = [NSString stringWithFormat:@"%li", articlePerPage];
    }
    if (userCategories) {
        if (userCategories.count > 10) {
            completion(NO, nil, [NSError PIXErrorWithParameterName:@"個人自行定義的分類最多只能10個"]);
            return;
        }
        for (id value in userCategories) {
            if (![value isMemberOfClass:[NSString class]]) {
                completion(NO, nil, [NSError PIXErrorWithParameterName:@"個人自行定義的分類裡每個值都一定要是 NSString"]);
                return;
            }
        }
        params[@"category_id"] = [userCategories componentsJoinedByString:@","];
    }
    if (status >= 0) {
        params[@"status"] = [NSString stringWithFormat:@"%li", status];
    }
    params[@"is_top"] = [NSString stringWithFormat:@"%i", isTop];
    params[@"trim_user"] = [NSString stringWithFormat:@"%i", trimUser];
    
    [[PIXAPIHandler new] callAPI:@"blog/articles"
                      parameters:params
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
                   if (succeed) {
                       [self succeedHandleWithData:result completion:completion];
                   } else {
                       completion(NO, nil, errorMessage);
                   }
               }];
}

- (void)getBlogSingleArticleWithUserName:(NSString *)userName
                               articleID:(NSString *)articleID
                            blogPassword:(NSString *)blogPasswd
                         articlePassword:(NSString *)articlePasswd
                              completion:(PIXHandlerCompletion)completion{
    
    if (userName == nil || userName.length == 0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing User Name"]);
        return;
    }
    if (articleID == nil || articleID.length == 0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing Article ID"]);
        return;
    }
    
    
    NSMutableDictionary *params = [NSMutableDictionary new];
    params[@"user"] = userName;
    if (blogPasswd != nil) {
        params[@"blog_password"] = blogPasswd;
    }
    if (articlePasswd != nil) {
        params[@"article_password"] = articlePasswd;
    }
    
    [[PIXAPIHandler new] callAPI:[NSString stringWithFormat:@"blog/articles/%@", articleID]
                      parameters:params
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
                   if (succeed) {
                       [self succeedHandleWithData:result completion:completion];
                   } else {
                       completion(NO, nil, errorMessage);
                   }
               }];
}

- (void)getBlogRelatedArticleByArticleID:(NSString *)articleID
                                userName:(NSString *)userName
                                withBody:(BOOL)withBody
                            relatedLimit:(NSUInteger)limit
                              completion:(PIXHandlerCompletion)completion{
    if (userName == nil || userName.length == 0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing User Name"]);
        return;
    }
    if (articleID == nil || articleID.length == 0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing Article ID"]);
        return;
    }
    
    NSMutableDictionary *params = [NSMutableDictionary new];
    params[@"user"] = userName;
    if (limit > 0) {
        params[@"limit"] = [NSString stringWithFormat:@"%li", limit];
    }
    params[@"with_body"] = [NSString stringWithFormat:@"%i", withBody];
    [[PIXAPIHandler new] callAPI:[NSString stringWithFormat:@"blog/articles/%@/related", articleID]
                      parameters:params
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
                   if (succeed) {
                       [self succeedHandleWithData:result completion:completion];
                   } else {
                       completion(NO, nil, errorMessage);
                   }
               }];

}

- (void)getBlogArticleCommentsWithUserName:(NSString *)userName
                                 articleID:(NSString *)articleID
                              blogPassword:(NSString *)blogPasswd
                           articlePassword:(NSString *)articlePassword
                                      page:(NSUInteger)page
                           commentsPerPage:(NSUInteger)commentPerPage
                                completion:(PIXHandlerCompletion)completion{
    if (userName == nil || userName.length == 0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing User Name"]);
        return;
    }
    if (articleID == nil || articleID.length == 0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing Article ID"]);
        return;
    }
    
    NSMutableDictionary *params = [NSMutableDictionary new];

    params[@"user"] = userName;
    params[@"article_id"] = articleID;
    
    if (blogPasswd || blogPasswd.length != 0) {
        params[@"blog_password"] = blogPasswd;
    }
    if (articlePassword || articlePassword.length != 0) {
        params[@"article_password"] = articlePassword;
    }
    if (page) {
        params[@"page"] = @(page);
    }
    if (commentPerPage) {
        params[@"per_page"] = @(commentPerPage);
    }
    
    [[PIXAPIHandler new] callAPI:@"blog/comments"
                      parameters:params
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
                   if (succeed) {
                       [self succeedHandleWithData:result completion:completion];
                   } else {
                       completion(NO, nil, errorMessage);
                   }
               }];
}

- (void)getBlogLatestArticleWithUserName:(NSString *)userName
                              completion:(PIXHandlerCompletion)completion{
    if (userName == nil || userName.length == 0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing User Name"]);
        return;
    }
    NSMutableDictionary *params = [NSMutableDictionary new];
    
    params[@"user"] = userName;
    
    [[PIXAPIHandler new] callAPI:@"blog/articles/latest"
                      parameters:params
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
                   if (succeed) {
                       [self succeedHandleWithData:result completion:completion];
                   } else {
                       completion(NO, nil, errorMessage);
                   }
               }];
    
}

- (void)getBlogHotArticleWithUserName:(NSString *)userName
                             password:(NSString *)passwd
                           completion:(PIXHandlerCompletion)completion{
    
    if (userName == nil || userName.length == 0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing User Name"]);
        return;
    }
    NSMutableDictionary *params = [NSMutableDictionary new];
    
    params[@"user"] = userName;
    
    if (passwd || passwd.length >>0 || passwd !=nil) {
        params[@"blog_password"] = passwd;
    }
    
    
    [[PIXAPIHandler new] callAPI:@"blog/articles/hot"
                      parameters:params
              requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
                   if (succeed) {
                       [self succeedHandleWithData:result completion:completion];
                   } else {
                       completion(NO, nil, errorMessage);
                   }
               }];
}

- (void)getblogSearchArticleWithKeyword:(NSString *)keyword
                               userName:(NSString *)userName
                                   page:(NSUInteger)page
                                perPage:(NSUInteger)perPage
                             completion:(PIXHandlerCompletion)completion{
    
    if (keyword == nil || keyword.length == 0 || !keyword) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing Search String"]);
        return;
    }
    
    NSMutableDictionary *params = [NSMutableDictionary new];

    params[@"key"] = keyword;
 
    if (userName || userName.length >> 0 || userName != nil) {
        params[@"user"] = userName;
    } else {
        params[@"site"] = @"true";
    }
    
    if (page) {
        params[@"page"] = @(page);
    }
    
    if (perPage) {
        params[@"per_page"] = @(perPage);
    }
    
    
    [[PIXAPIHandler new] callAPI:@"blog/articles/search"
                      parameters:params
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
                   if (succeed) {
                       [self succeedHandleWithData:result completion:completion];
                   } else {
                       completion(NO, nil, errorMessage);
                   }
               }];
    
}
#pragma mark Article method need access token
- (void)createBlogArticleWithTitle:(NSString *)title
                              body:(NSString *)body
                            status:(PIXArticleStatus)status
                          publicAt:(NSDate *)date
                    userCategoryID:(NSString *)userCategoryId
                    siteCategoryID:(NSString *)cateID
                    useNewLineToBR:(BOOL)useNewLineToBR
                       commentPerm:(PIXArticleCommentPerm)commentPerm
                     commentHidden:(BOOL)commentHidden
                              tags:(NSArray *)tagArray
                          thumbURL:(NSString *)thumburl
                         trackback:(NSArray *)trackback
                          password:(NSString *)passwd
                      passwordHint:(NSString *)passwdHint
                     friendGroupID:(NSString *)friendGroupID
                     notifyTwitter:(BOOL)notifyTwitter
                    notifyFacebook:(BOOL)notifyFacebook
                        completion:(PIXHandlerCompletion)completion{
    [self createOrUpdateBlogArticleWithAPIPath:@"blog/articles"
                                     articleID:nil
                                         title:title
                                          body:body
                                        status:status
                                      publicAt:date
                                userCategoryID:userCategoryId
                                siteCategoryID:cateID
                                useNewLineToBR:useNewLineToBR
                                   commentPerm:commentPerm
                                 commentHidden:commentHidden
                                          tags:tagArray
                                      thumbURL:thumburl
                                     trackback:trackback
                                      password:passwd
                                  passwordHint:passwdHint
                                 friendGroupID:friendGroupID
                                 notifyTwitter:notifyTwitter
                                notifyFacebook:notifyFacebook
                                    completion:completion];
}
/*
 * 由於 create 及 update article 的參數都一樣，所以用這個 method 合併處理
 */
- (void)createOrUpdateBlogArticleWithAPIPath:(NSString *)path
                                   articleID:(NSString *)articleId
                                         title:(NSString *)title
                                          body:(NSString *)body
                                        status:(PIXArticleStatus)status
                                    publicAt:(NSDate *)date
                                userCategoryID:(NSString *)userCategoryId
                                siteCategoryID:(NSString *)cateID
                                useNewLineToBR:(BOOL)useNewLineToBR
                                   commentPerm:(PIXArticleCommentPerm)commentPerm
                                 commentHidden:(BOOL)commentHidden
                                          tags:(NSArray *)tagArray
                                      thumbURL:(NSString *)thumburl
                                     trackback:(NSArray *)trackback
                                      password:(NSString *)passwd
                                  passwordHint:(NSString *)passwdHint
                                 friendGroupID:(NSString *)friendGroupID
                                 notifyTwitter:(BOOL)notifyTwitter
                                notifyFacebook:(BOOL)notifyFacebook
                                    completion:(PIXHandlerCompletion)completion{
    BOOL isCreating = [path isEqualToString:@"blog/articles"];

    if (isCreating && (title == nil || title.length == 0)) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing Article Title"]);
        return;
    }
    if (isCreating && (body == nil || body.length == 0)) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing Article Body"]);
        return;
    }
    if (!isCreating && (articleId==nil || articleId.length==0)) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing Article Id"]);
        return;
    }
    
    if (status == PIXArticleStatusPassword) {
        if (passwd == nil || passwd.length == 0) {
            completion(NO, nil, [NSError PIXErrorWithParameterName:@"請輸入欲設定之文章密碼"]);
            return;
        }else if (passwdHint == nil || passwdHint.length == 0){
            completion(NO, nil, [NSError PIXErrorWithParameterName:@"請輸入欲設定文章密碼提示"]);
            return;
        }
    }
    NSMutableDictionary *params = [NSMutableDictionary new];
    if (title && title.length>0) {
        params[@"title"] = title;
    }
    if (body && body.length>0) {
        params[@"body"] = body;
    }
    
    params[@"status"] = [NSString stringWithFormat:@"%li", status];
    
    if (date) {
        params[@"public_at"] = [NSString stringWithFormat:@"%g", [date timeIntervalSince1970]];
    }
    
    if (userCategoryId!=nil && userCategoryId.length>0) {
        params[@"category_id"] = userCategoryId;
    }
    if (cateID!=nil && cateID.length>0) {
        params[@"site_category_id"] = cateID;
    }
    params[@"use_nl2br"] = [NSString stringWithFormat:@"%i", useNewLineToBR];

    params[@"comment_perm"] = [NSString stringWithFormat:@"%li", commentPerm];
    
    params[@"comment_hidden"] = [NSString stringWithFormat:@"%i", commentHidden];
    
    if (tagArray) {
        for (id value in tagArray) {
            if (![value isMemberOfClass:[NSString class]]) {
                completion(NO, nil, [NSError PIXErrorWithParameterName:@"tagArray 裡的每個值都一定要是 NSString 物件"]);
                return;
            }
        }
        params[@"tags"] = [tagArray componentsJoinedByString:@","];
    }
    if (thumburl && thumburl.length!=0) {
        params[@"thumb"] = thumburl;
    }
    if (trackback && trackback.count>0) {
        for (id value in trackback) {
            if (![value isMemberOfClass:[NSString class]]) {
                completion(NO, nil, [NSError PIXErrorWithParameterName:@"trackback 裡每一個值都一定要是 NSString 物件"]);
                return;
            }
        }
        params[@"trackback"] = trackback;
    }
    if (status == PIXArticleStatusPassword) {
        params[@"password"] = passwd;
        params[@"password_hint"] = passwdHint;
    }
    
    if (status == PIXArticleStatusFriend && friendGroupID) {
        params[@"friend_group_ids"] = friendGroupID;
    }
    if (notifyTwitter >= 0) {
        params[@"notify_twitter"] = [NSString stringWithFormat:@"%i", notifyTwitter];
    }
    if (notifyFacebook >= 0) {
        params[@"notify_facebook"] = [NSString stringWithFormat:@"%i", notifyFacebook];
    }
    [[PIXAPIHandler new] callAPI:path
                      httpMethod:@"POST"
                      shouldAuth:YES
                      parameters:params
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
                   if (succeed) {
                       [self succeedHandleWithData:result completion:completion];
                   } else {
                       completion(NO, nil, errorMessage);
                   }
               }];
}
- (void)updateBlogArticleWithArticleID:(NSString *)articleID
                                 title:(NSString *)title
                                  body:(NSString *)body
                                status:(PIXArticleStatus)status
                              publicAt:(NSDate *)date
                        userCategoryID:(NSString *)userCategoryId
                        siteCategoryID:(NSString *)cateID
                        useNewLineToBR:(BOOL)useNewLineToBR
                           commentPerm:(PIXArticleCommentPerm)commentPerm
                         commentHidden:(BOOL)commentHidden
                                  tags:(NSArray *)tagArray
                              thumbURL:(NSString *)thumburl
                             trackback:(NSArray *)trackback
                              password:(NSString *)passwd
                          passwordHint:(NSString *)passwdHint
                         friendGroupID:(NSString *)friendGroupID
                         notifyTwitter:(BOOL)notifyTwitter
                        notifyFacebook:(BOOL)notifyFacebook
                            completion:(PIXHandlerCompletion)completion{
    if (articleID==nil || articleID.length==0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing Article ID"]);
        return;
    }
    [self createOrUpdateBlogArticleWithAPIPath:[NSString stringWithFormat:@"blog/articles/%@", articleID]
                                     articleID:articleID
                                         title:title
                                          body:body
                                        status:status
                                      publicAt:date
                                userCategoryID:userCategoryId
                                siteCategoryID:cateID
                                useNewLineToBR:useNewLineToBR
                                   commentPerm:commentPerm
                                 commentHidden:commentHidden
                                          tags:tagArray
                                      thumbURL:thumburl
                                     trackback:trackback
                                      password:passwd
                                  passwordHint:passwdHint
                                 friendGroupID:friendGroupID
                                 notifyTwitter:notifyTwitter
                                notifyFacebook:notifyFacebook
                                    completion:completion];
}

- (void)deleteBlogArticleByArticleID:(NSString *)articleID
                          completion:(PIXHandlerCompletion)completion{
    
    if (articleID == nil || articleID.length == 0 || !articleID) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing Article ID"]);
        return;
    }
    
    NSMutableDictionary *params = [NSMutableDictionary new];
    params[@"_method"] = @"delete";
    
    [[PIXAPIHandler new] callAPI:[NSString stringWithFormat:@"blog/articles/%@", articleID]
                      httpMethod:@"POST"
                      shouldAuth:YES
                      parameters:params
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
                   if (succeed) {
                       [self succeedHandleWithData:result completion:completion];
                   } else {
                       completion(NO, nil, errorMessage);
                   }
               }];

}

#pragma mark - Blog Comments

- (void)getBlogCommentsWithUserName:(NSString *)userName
                          articleID:(NSString *)articleID
                               page:(NSUInteger)page
                            perPage:(NSUInteger)perPage
                         completion:(PIXHandlerCompletion)completion{
    
    if (userName == nil || userName.length == 0 || !userName) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing User Name"]);
        return;
    }
    
    if (articleID == nil || articleID.length == 0 || !articleID) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing Article ID"]);
        return;
    }
    NSMutableDictionary *params = [NSMutableDictionary new];
    
    params[@"user"] = userName;
    params[@"article_id"] = articleID;
    
    if (page) {
        params[@"page"] = @(page);
    }
    if (perPage) {
        params[@"per_page"] = @(perPage);
    }
    
    [[PIXAPIHandler new] callAPI:@"blog/comments"
                      parameters:params
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
                   if (succeed) {
                       [self succeedHandleWithData:result completion:completion];
                   } else {
                       completion(NO, nil, errorMessage);
                   }
               }];

}

- (void)getBlogSingleCommentWithUserName:(NSString *)userName
                              commmentID:(NSString *)commentID
                              completion:(PIXHandlerCompletion)completion{
    if (userName == nil || userName.length == 0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing User Name"]);
        return;
    }
    
    if (commentID == nil || commentID.length == 0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing Comment ID"]);
        return;
    }
    NSMutableDictionary *params = [NSMutableDictionary new];
    
    params[@"user"] = userName;
    
    [[PIXAPIHandler new] callAPI:[NSString stringWithFormat:@"blog/comments/%@", commentID]
                      parameters:params
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
                   if (succeed) {
                       [self succeedHandleWithData:result completion:completion];
                   } else {
                       completion(NO, nil, errorMessage);
                   }
               }];
}

- (void)getBlogLatestCommentWithUserName:(NSString *)userName
                              completion:(PIXHandlerCompletion)completion{
    
    NSMutableDictionary *params = [NSMutableDictionary new];

    if (userName || userName != nil || userName.length >> 0) {
        params[@"user"] = userName;
    }
    
    [[PIXAPIHandler new] callAPI:@"blog/comments/latest"
                      parameters:params
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
                   if (succeed) {
                       [self succeedHandleWithData:result completion:completion];
                   } else {
                       completion(NO, nil, errorMessage);
                   }
               }];
    
}
#pragma mark Comment Method need access token

- (void)createBlogCommentWithArticleID:(NSString *)articleID
                                  body:(NSString *)body
                              userName:(NSString *)userName
                                author:(NSString *)author
                                 title:(NSString *)title
                                   url:(NSString *)url
                                isOpen:(BOOL)isOpen
                                 email:(NSString *)email
                          blogPassword:(NSString *)blogPasswd
                       articlePassword:(NSString *)articlePasswd
                            completion:(PIXHandlerCompletion)completion{

    if (!articleID || articleID == nil || articleID.length == 0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing Article ID"]);
        return;
    }
    if (!body || body == nil || body.length == 0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing Comment Body"]);
        return;
    }
    
    NSMutableDictionary *params = [NSMutableDictionary new];
    params[@"article_id"] = articleID;
    params[@"body"] = body;
    
    if (userName || userName != nil || userName.length != 0) {
        params[@"user"] = userName;
    }
    
    if (author || author != nil || author.length != 0) {
        params[@"author"] = author;
    }
    
    if (title || title != nil || title.length != 0) {
        params[@"title"] = title;
    }
    
    if (url || url != nil || url.length != 0) {
        params[@"url"] = url;
    }
    
    if (isOpen) {
        params[@"is_open"] = @"0";
    }else{
        params[@"is_open"] = @"1";
    }
    
    if (email || email != nil || email.length != 0) {
        params[@"email"] = email;
    }
    
    if (blogPasswd || blogPasswd != nil || blogPasswd.length != 0) {
        params[@"blog_password"] = blogPasswd;
    }
    
    if (articlePasswd || articlePasswd != nil || articlePasswd.length != 0) {
        params[@"article_password"] = articlePasswd;
    }
    
    [[PIXAPIHandler new] callAPI:@"blog/comments"
                      httpMethod:@"POST"
                      shouldAuth:YES
                      parameters:params
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
                   if (succeed) {
                       [self succeedHandleWithData:result completion:completion];
                   } else {
                       completion(NO, nil, errorMessage);
                   }
               }];
}

- (void)replyBlogCommentWithCommnetID:(NSString *)commentID
                                 body:(NSString *)body
                           completion:(PIXHandlerCompletion)completion{
    if (!commentID || commentID == nil || commentID.length == 0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing Comment ID"]);
        return;
    }
    
    if (!body || body == nil || body.length == 0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing Comment Body"]);
        return;
    }
    
    NSMutableDictionary *params = [NSMutableDictionary new];
    params[@"body"] = body;
    
    [[PIXAPIHandler new] callAPI:[NSString stringWithFormat:@"blog/comments/%@/reply", commentID]
                      httpMethod:@"POST"
                      shouldAuth:YES
                      parameters:params
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
                   if (succeed) {
                       [self succeedHandleWithData:result completion:completion];
                   } else {
                       completion(NO, nil, errorMessage);
                   }
               }];
}


- (void)updateBlogCommentOpenWithCommentID:(NSString *)commentID
                                    isOpen:(BOOL)isOpen
                                completion:(PIXHandlerCompletion)completion{
    if (!commentID || commentID == nil || commentID.length == 0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing Comment ID"]);
        return;
    }
    NSString *isOpenString = [NSString new];
    
    if (isOpen) {
        isOpenString = @"open";
    }else{
        isOpenString = @"close";
    }
    
    [[PIXAPIHandler new] callAPI:[NSString stringWithFormat:@"blog/comments/%@/%@", commentID, isOpenString]
                      httpMethod:@"POST"
                      shouldAuth:YES
                      parameters:nil
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
                   if (succeed) {
                       [self succeedHandleWithData:result completion:completion];
                   } else {
                       completion(NO, nil, errorMessage);
                   }
               }];
    
}


- (void)updateBlogCommentSpamWithCommentID:(NSString *)commentID
                                    isSpam:(BOOL)isSpam
                                completion:(PIXHandlerCompletion)completion{
    
    if (!commentID || commentID == nil || commentID.length == 0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing Comment ID"]);
        return;
    }
    
    NSString *isSpamString = [NSString new];
    
    if (isSpam) {
        isSpamString = @"mark_spam";
    }else{
        isSpamString = @"mark_ham";
    }
    
    [[PIXAPIHandler new] callAPI:[NSString stringWithFormat:@"blog/comments/%@/%@", commentID, isSpamString]
                      httpMethod:@"POST"
                      shouldAuth:YES
                      parameters:nil
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
                   if (succeed) {
                       [self succeedHandleWithData:result completion:completion];
                   } else {
                       completion(NO, nil, errorMessage);
                   }
               }];
    
}

- (void)deleteBlogCommentWithCommentID:(NSString *)commentID
                            completion:(PIXHandlerCompletion)completion{

    if (!commentID || commentID == nil || commentID.length == 0) {
        completion(NO, nil, [NSError PIXErrorWithParameterName:@"Missing Comment ID"]);
        return;
    }
    
    NSMutableDictionary *params = [NSMutableDictionary new];
    params[@"_method"] = @"delete";
    
    [[PIXAPIHandler new] callAPI:[NSString stringWithFormat:@"blog/comments/%@", commentID]
                      httpMethod:@"POST"
                      shouldAuth:YES
                      parameters:nil
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
                   if (succeed) {
                       [self succeedHandleWithData:result completion:completion];
                   } else {
                       completion(NO, nil, errorMessage);
                   }
               }];
}


#pragma mark - Site Blog Categories list

- (void)getBlogCategoriesListIncludeGroups:(BOOL)group
                                    thumbs:(BOOL)thumb
                                completion:(PIXHandlerCompletion)completion{
    
    NSMutableDictionary *params = [NSMutableDictionary new];
    
    params[@"include_groups"] = [NSString stringWithFormat:@"%i", group];
    params[@"include_thumbs"] = [NSString stringWithFormat:@"%i", thumb];
    
    [[PIXAPIHandler new] callAPI:@"blog/site_categories"
                      parameters:params
               requestCompletion:^(BOOL succeed, id result, NSError *errorMessage) {
                   if (succeed) {
                       [self succeedHandleWithData:result completion:completion];
                   } else {
                       completion(NO, nil, errorMessage);
                   }
               }];
    
}
@end
