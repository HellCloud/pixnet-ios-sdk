//
//  PIXNETSDK.h
//  PIXNET-iOS-SDK
//
//  Created by Cloud Sung on 2014/3/13.
//  Copyright (c) 2014年 PIXNET. All rights reserved.
//


#import <Foundation/Foundation.h>
@class PIXBlog;
#import "PIXAPIHandler.h"
#import "PIXAlbum.h"
#import "PIXBlog.h"

@interface PIXNETSDK : NSObject

/**
 *  呼叫任何 API 前，務必設定 consumer key 及 consumer secret
 *
 *  @param aKey     consum key
 *  @param aSecret consumer secret
 */
+(void)setConsumerKey:(NSString *)aKey consumerSecret:(NSString *)aSecret;
/**
 *  利用 XAuth 向 PIXNET 後台取得授權
 *
 *  @param userName   使用者名稱(帳號)
 *  @param password   使用者密碼
 *  @param completion succeed == YES 時，回傳 token; succeed == NO 時，則會回傳 errorMessage
 */
+(void)authByXauthWithUserName:(NSString *)userName userPassword:(NSString *)password requestCompletion:(PIXHandlerCompletion)completion;
+(instancetype)sharedInstance;

//Blog Method

#pragma mark - Blog Method
#pragma mark - Blog imformation
/**
 *  列出部落格資訊 http://emma.pixnet.cc/blog
 *
 *  @param userName   ＊指定要回傳的使用者資訊
 *  @param completion succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)getBlogInformationWithUserName:(NSString *)userName
                            completion:(PIXHandlerCompletion)completion;

#pragma mark - Blog Categories
//dosen't need Access token
/**
 *  讀取使用者部落格分類資訊 http://emma.pixnet.cc/blog/categories
 *
 *  @param userName   *指定要回傳的使用者資訊
 *  @param passwd     如果指定使用者的 Blog 被密碼保護，則需要指定這個參數以通過授權，沒有則輸入 nil
 *  @param completion succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)getBlogCategoriesWithUserName:(NSString *)userName
                             password:(NSString *)passwd
                           completion:(PIXHandlerCompletion)completion;

#pragma mark Categories method need access token
/**
 *  新增部落格個人分類（需認證） http://emma.pixnet.cc/blog/categories
 *
 *  @param name        *分類名稱
 *  @param type        *請輸入分類 PIXBlogCategoryType 型別，有 Folder 及 Category 可選
 *  @param description 分類說明
 *  @param cateID      *對應的全站文章類別 id. 當 type 為 category 為必須參數
 *  @param completion  succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)createBlogCategoriesWithName:(NSString *)name
                                type:(PIXBlogCategoryType)type
                         description:(NSString *)description
                        siteCategory:(PIXSiteBlogCategory)siteCateID
                          completion:(PIXHandlerCompletion)completion;
/**
 *  修改部落格個人分類 (需認證) http://emma.pixnet.cc/blog/categories/:id
 *
 *  @param categoriesID *要修改的 Category / Folder ID
 *  @param newName      *修改後的顯示名稱
 *  @param type         要修改的類型是 Category / Folder
 *  @param description  修改後的分類說明
 *  @param completion   succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)updateBlogCategoriesFromID:(NSString *)categoriesID
                           newName:(NSString *)newName
                              type:(PIXBlogCategoryType)type
                       description:(NSString *)description
                        completion:(PIXHandlerCompletion)completion;
/**
 *  刪除部落格個人分類 http://emma.pixnet.cc/blog/categories/:id
 *
 *
 *  @param categoriesID *要刪除的 Category ID
 *  @param completion   succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)deleteBlogCategoriesByID:(NSString *)categoriesID
                      completion:(PIXHandlerCompletion)completion;

/**
 *  刪除部落格個人資料夾 http://emma.pixnet.cc/blog/categories/:id
 *
 *  @param categoriesID *要刪除的 Folder ID
 *  @param completion   succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)deleteBlogFolderByID:(NSString *)folderID
                  completion:(PIXHandlerCompletion)completion;


/**
 *  修改部落格分類排序 http://emma.pixnet.cc/blog/categories/position
 *
 *  @param categoriesIDArray *輸入以部落格分類ID組成已排序好的 Array，分類將會已陣列順序重新排序。放在越前面的表示圖片的順序越優先。不過在排序上分類資料夾的排序要優先於分類，所以對分類資料夾的排序指定只會影響資料夾群本身
 *  @param completion        succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)sortBlogCategoriesTo:(NSArray *)categoriesIDArray
                  completion:(PIXHandlerCompletion)completion;


#pragma mark - Blog Articles
//dosen't need Access token
/**
 *  列出部落格個人文章 http://emma.pixnet.cc/blog/articles
 *
 *  @param userName       ＊指定要回傳的使用者資訊
 *  @param passwd         如果指定使用者的 Blog 被密碼保護，則需要指定這個參數以通過授權，沒有則輸入 nil
 *  @param page           頁數, 預設為 1, 不需要則輸入 nil
 *  @param articlePerPage 每頁幾筆, 預設為 100, 不需要則輸入 nil
 *  @param completion     succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)getBlogAllArticlesWithUserName:(NSString *)userName
                              password:(NSString *)passwd
                                  page:(NSUInteger)page
                               perpage:(NSUInteger)articlePerPage
                            completion:(PIXHandlerCompletion)completion;

/**
 *  讀取部落格個人文章 http://emma.pixnet.cc/blog/articles/:id
 *
 *  @param userName      ＊指定要回傳的使用者資訊
 *  @param articleID     ＊指定要回傳的文章ID
 *  @param blogPasswd    如果指定使用者的 Blog 被密碼保護，則需要指定這個參數以通過授權，沒有則輸入 nil
 *  @param articlePasswd 如果指定使用者的文章被密碼保護，則需要指定這個參數以通過授權，沒有則輸入 nil
 *  @param completion    succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)getBlogSingleArticleWithUserName:(NSString *)userName
                               articleID:(NSString *)articleID
                            blogPassword:(NSString *)blogPasswd
                         articlePassword:(NSString *)articlePasswd
                              completion:(PIXHandlerCompletion)completion;

/**
 *  讀取指定 ID 文章的相關文章 http://emma.pixnet.cc/blog/articles/:id/related
 *
 *  @param articleID  ＊指定要回傳的文章ID
 *  @param userName   ＊指定要回傳的使用者
 *  @param limit      限制回傳文章的筆數，預設值為1，最大值為10, 不設定則輸入 nil
 *  @param completion succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)getBlogRelatedArticleByArticleID:(NSString *)articleID
                                userName:(NSString *)userName
                            relatedLimit:(NSUInteger)limit
                              completion:(PIXHandlerCompletion)completion;

/**
 *  列出部落格留言 http://emma.pixnet.cc/blog/comments
 *
 *  @param userName        *指定要回傳的使用者資訊
 *  @param articleID       *指定要回傳的留言文章
 *  @param blogPasswd      如果指定使用者的 Blog 被密碼保護，則需要指定這個參數以通過授權，沒有則輸入 nil
 *  @param articlePassword 如果指定使用者的文章被密碼保護，則需要指定這個參數以通過授權，沒有則輸入 nil
 *  @param page            頁數, 預設為 1, 不需要則輸入 nil
 *  @param commentPerPage  每頁幾筆, 預設為 100, 不需要則輸入 nil
 *  @param completion      succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)getBlogArticleCommentsWithUserName:(NSString *)userName
                                 articleID:(NSString *)articleID
                              blogPassword:(NSString *)blogPasswd
                           articlePassword:(NSString *)articlePassword
                                      page:(NSUInteger)page
                           commentsPerPage:(NSUInteger)commentPerPage
                                completion:(PIXHandlerCompletion)completion;
/**
 *  列出部落格最新文章 http://emma.pixnet.cc/blog/articles/latest
 *
 *  @param userName   *指定要回傳的使用者資訊
 *  @param completion succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)getBlogLatestArticleWithUserName:(NSString *)userName
                              completion:(PIXHandlerCompletion)completion;

/**
 *  列出部落格熱門文章 http://emma.pixnet.cc/blog/articles/hot
 *
 *  @param userName   *指定要回傳的使用者資訊
 *  @param passwd     如果指定使用者的 Blog 被密碼保護，則需要指定這個參數以通過授權，沒有則輸入 nil
 *  @param completion succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)getBlogHotArticleWithUserName:(NSString *)userName
                             password:(NSString *)passwd
                           completion:(PIXHandlerCompletion)completion;

/**
 *  搜尋部落格個人文章 http://emma.pixnet.cc/blog/articles/search
 *
 *  @param keyword    *關鍵字或標籤
 *  @param userName   指定要回傳的使用者資訊，如輸入 nil 則搜尋全站
 *  @param page       頁數, 預設為 1, 不需要則輸入 nil
 *  @param perPage    每頁幾筆, 預設為 100, 不需要則輸入 nil
 *  @param completion succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)getblogSearchArticleWithKeyword:(NSString *)keyword
                               userName:(NSString *)userName
                                   page:(NSUInteger)page
                                perPage:(NSUInteger)perPage
                             completion:(PIXHandlerCompletion)completion;

#pragma mark Article method need access token
/**
 *  新增部落格個人文章 http://emma.pixnet.cc/blog/articles
 *
 *  @param title         *文章標題
 *  @param body          *文章內容
 *  @param status        文章狀態，使用 PIXArticleStatus 型別
 *  @param date          公開時間，這個表示文章的發表時間，預設為現在時間
 *  @param cateID        全站分類，使用 PIXSiteBlogCategory 型別
 *  @param commentPerm   可留言權限，使用 PIXArticleCommentPerm 型別
 *  @param commentHidden 預設留言狀態， Yes 為強制隱藏 NO 為顯示(公開)，預設為 NO 公開(顯示)
 *  @param tagArray      文章標籤
 *  @param thumburl      文章縮圖網址, 會影響 oEmbed 與 SNS (Twitter, Facebook, Plurk …) 抓到的縮圖
 *  @param passwd        當 status 被設定為 PIXArticleStatusPassword 時需要輸入這個參數以設定為此文章的密碼
 *  @param passwdHint    當 status 被設定為 PIXArticleStatusPassword 時需要輸入這個參數以設定為此文章的密碼提示
 *  @param friendGroupID 當 status 被設定為 PIXArticleStatusFriend 時可以輸入這個參數以設定此文章可閱讀的好友群組, 預設不輸入代表所有好友
 *  @param completion    succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)createBlogArticleWithTitle:(NSString *)title
                              body:(NSString *)body
                            status:(PIXArticleStatus)status
                          publicAt:(NSDate *)date
                    siteCategoryID:(PIXSiteBlogCategory)cateID
                       commentPerm:(PIXArticleCommentPerm)commentPerm
                     commentHidden:(BOOL)commentHidden
                              tags:(NSArray *)tagArray
                          thumbURL:(NSString *)thumburl
                          password:(NSString *)passwd
                      passwordHine:(NSString *)passwdHint
                     friendGroupID:(NSString *)friendGroupID
                        completion:(PIXHandlerCompletion)completion;
/**
 *  修改部落格個人文章 http://emma.pixnet.cc/blog/articles/:id
 *
 *  @param articleID     *要修改的文章 ID
 *  @param title         *修改後的文章標題
 *  @param body          *修改後的文章內容
 *  @param status        文章狀態，使用 PIXArticleStatus 型別
 *  @param date          公開時間，這個表示文章的發表時間，預設為現在時間
 *  @param cateID        全站分類，使用 PIXSiteBlogCategory 型別
 *  @param commentPerm   可留言權限，使用 PIXArticleCommentPerm 型別
 *  @param commentHidden 預設留言狀態， Yes 為強制隱藏 NO 為顯示(公開)，預設為 NO 公開(顯示)
 *  @param tagArray      文章標籤
 *  @param thumburl      文章縮圖網址, 會影響 oEmbed 與 SNS (Twitter, Facebook, Plurk …) 抓到的縮圖
 *  @param passwd        當 status 被設定為 PIXArticleStatusPassword 時需要輸入這個參數以設定為此文章的密碼
 *  @param passwdHint    當 status 被設定為 PIXArticleStatusPassword 時需要輸入這個參數以設定為此文章的密碼提示
 *  @param friendGroupID 當 status 被設定為 PIXArticleStatusFriend 時可以輸入這個參數以設定此文章可閱讀的好友群組, 預設不輸入代表所有好友
 *  @param completion    succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)updateBlogArticleWithArticleID:(NSString *)articleID
                                 title:(NSString *)title
                                  body:(NSString *)body
                                status:(PIXArticleStatus)status
                              publicAt:(NSDate *)date
                        siteCategoryID:(PIXSiteBlogCategory)cateID
                           commentPerm:(PIXArticleCommentPerm)commentPerm
                         commentHidden:(BOOL)commentHidden
                                  tags:(NSArray *)tagArray
                              thumbURL:(NSString *)thumburl
                              password:(NSString *)passwd
                          passwordHine:(NSString *)passwdHint
                         friendGroupID:(NSString *)friendGroupID
                            completion:(PIXHandlerCompletion)completion;

/**
 *  刪除部落格個人文章 http://emma.pixnet.cc/blog/articles/:id
 *
 *  @param articleID  *要刪除的文章 ID
 *  @param completion succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)deleteBlogArticleByArticleID:(NSString *)articleID
                          completion:(PIXHandlerCompletion)completion;



#pragma mark - Blog Comments
//dosen't need Access token

/**
 *  列出部落格留言 http://emma.pixnet.cc/blog/comments
 *
 *  @param userName   *指定要回傳的使用者資訊
 *  @param articleID  *指定要回傳的留言文章
 *  @param page       頁數, 預設為 1, 不需要則輸入 nil
 *  @param perPage    每頁幾筆, 預設為 100, 不需要則輸入 nil
 *  @param completion succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)getBlogCommentsWithUserName:(NSString *)userName
                          articleID:(NSString *)articleID
                               page:(NSUInteger)page
                            perPage:(NSUInteger)perPage
                         completion:(PIXHandlerCompletion)completion;

/**
 *  讀取單一留言 http://emma.pixnet.cc/blog/comments/:id
 *
 *  @param userName   *指定要回傳的使用者資訊
 *  @param commentID  *指定要回傳的留言ID
 *  @param completion succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)getBlogSingleCommentWithUserName:(NSString *)userName
                              commmentID:(NSString *)commentID
                              completion:(PIXHandlerCompletion)completion;


/**
 *  列出部落格最新留言 http://emma.pixnet.cc/blog/comments/latest
 *
 *  @param userName   ＊指定要回傳的使用者資訊
 *  @param completion succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)getBlogLatestCommentWithUserName:(NSString *)userName
                              completion:(PIXHandlerCompletion)completion;


#pragma mark Comment method need access token

/**
 *  新增部落格留言 http://emma.pixnet.cc/blog/comments
 *
 *  @param articleID     *要留言的文章 ID
 *  @param body          *留言內容
 *  @param userName      要留言的部落格作者名稱, 若不填入則預設找自己的文章
 *  @param author        留言的暱稱, 不填入則預設代入認證使用者的 display_name
 *  @param title         留言標題
 *  @param url           留言者個人網頁
 *  @param isOpen        公開留言/悄悄話
 *  @param email         留言者電子郵件
 *  @param blogPasswd    如果指定使用者的 Blog 被密碼保護，則需要指定這個參數以通過授權
 *  @param articlePasswd 如果指定使用者的文章被密碼保護，則需要指定這個參數以通過授權
 *  @param completion    succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
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
                            completion:(PIXHandlerCompletion)completion;
/**
 *  回覆部落格留言，可以重覆使用這個功能來修改回覆內容 http://emma.pixnet.cc/blog/comments/:id/reply
 *
 *  @param commentID  *要回覆/修改的留言 ID
 *  @param body       *留言內容/修改後的內容
 *  @param completion succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)replyBlogCommentWithCommnetID:(NSString *)commentID
                                 body:(NSString *)body
                           completion:(PIXHandlerCompletion)completion;

/**
 *  將留言設為公開/關閉 http://emma.pixnet.cc/blog/comments/:id/open http://emma.pixnet.cc/blog/comments/:id/close
 *
 *  @param commentID  *要公開/關閉的留言 ID
 *  @param isOpen     * YSE 為 公開， NO 為 關閉 該則留言
 *  @param completion succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)updateBlogCommentOpenWithCommentID:(NSString *)commentID
                                    isOpen:(BOOL)isOpen
                                completion:(PIXHandlerCompletion)completion;

/**
 *  將留言設為廣告留言/非廣告留言 http://emma.pixnet.cc/blog/comments/:id/mark_spam http://emma.pixnet.cc/blog/comments/:id/mark_ham
 *
 *  @param commentID  *要公開/關閉的留言 ID
 *  @param isSpam     * YSE 為設成廣告留言， NO 為設成非廣告留言
 *  @param completion succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)updateBlogCommentSpamWithCommentID:(NSString *)commentID
                                    isSpam:(BOOL)isSpam
                                completion:(PIXHandlerCompletion)completion;

/**
 *  刪除部落格留言 http://emma.pixnet.cc/blog/comments/:id
 *
 *  @param commentID  *要刪除的留言 ID
 *  @param completion succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)deleteBlogCommentWithCommentID:(NSString *)commentID
                            completion:(PIXHandlerCompletion)completion;


#pragma mark - Site Blog Categories list

/**
 *  列出部落格全站分類 http://emma.pixnet.cc/blog/site_categories
 *
 *  @param group      當被設為 YES 或 true 時, 回傳資訊會以全站分類群組為分類，不需要則輸入 NO 或 false
 *  @param thumb      當被設為 YES 或 true 時, 回傳分類資訊會包含縮圖網址，不需要則輸入 NO 或 false
 *  @param completion succeed = YES 時 result 可以用 (errorMessage == nil)，succeed = NO 時 result 會是 nil，錯誤原因會在 errorMessage 裡
 */
- (void)getBlogCategoriesListIncludeGroups:(BOOL)group
                                    thumbs:(BOOL)thumb
                                completion:(PIXHandlerCompletion)completion;


#pragma mark album(相簿)
#pragma mark site categories
/**
 *  列出相簿全站分類 http://developer.pixnet.pro/#!/doc/pixnetApi/albumSiteCategories
 *
 *  @param isIncludeGroups 當被設為 YES 時, 回傳資訊會以全站分類群組為分類
 *  @param isIncludeThumbs 當被設為 YES 時, 回傳分類資訊會包含縮圖
 *  @param completion      succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)getAlbumSiteCategoriesWithIsIncludeGroups:(BOOL)isIncludeGroups isIncludeThumbs:(BOOL)isIncludeThumbs completion:(PIXHandlerCompletion)completion;
#pragma mark Main
/**
 *  列出相簿主圖及相片牆資訊 http://developer.pixnet.pro/#!/doc/pixnetApi/albumMain
 *
 *  @param completion succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)getAlbumMainWithCompletion:(PIXHandlerCompletion)completion;
#pragma mark config
/**
 *  列出相簿個人設定 http://developer.pixnet.pro/#!/doc/pixnetApi/albumConfig
 *
 *  @param completion succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)getAlbumConfigWithCompletion:(PIXHandlerCompletion)completion;
#pragma mark SetFolders
/**
 *  列出相本列表,每頁20筆 http://developer.pixnet.pro/#!/doc/pixnetApi/albumSetfolders
 *
 *  @param userName   相本擁有者,必要參數
 *  @param page       頁數
 *  @param completion succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)getAlbumSetsWithUserName:(NSString *)userName page:(NSUInteger)page completion:(PIXHandlerCompletion)completion;

/**
 *  修改相簿首頁排序 http://developer.pixnet.pro/#!/doc/pixnetApi/albumSetfoldersPosition
 *
 *  @param ids        相簿id, array 裡的值為 NSString, id 的順序即為相簿的新順序
 *  @param completion succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)sortSetFoldersWithFolderIDs:(NSArray *)ids completion:(PIXHandlerCompletion)completion;
#pragma mark Sets
/**
 *  列出個人所有相本 http://developer.pixnet.pro/#!/doc/pixnetApi/albumSets
 *
 *  @param userName   相本擁有者,必要參數
 *  @param parentID   可以藉此指定拿到特定相簿資料夾底下的相簿
 *  @param page       頁數
 *  @param completion succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)getAlbumSetsWithUserName:(NSString *)userName parentID:(NSString *)parentID page:(NSUInteger)page completion:(PIXHandlerCompletion)completion;
/**
 *  讀取個人某一本相本 http://developer.pixnet.pro/#!/doc/pixnetApi/albumSetsShow
 *
 *  @param userName   相本擁有者, 必要參數
 *  @param setId      指定要回傳的 set 的 ID, 必要參數
 *  @param page       頁數
 *  @param completion succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)getAlbumSetWithUserName:(NSString *)userName setID:(NSString *)setId page:(NSUInteger)page completion:(PIXHandlerCompletion)completion;
/**
 *  新增相簿 http://developer.pixnet.pro/#!/doc/pixnetApi/albumSetsCreate
 *
 *  @param setTitle           相簿標題，必要參數
 *  @param setDescription     相簿描述，必要參數
 *  @param permission         相簿閱讀權限
 *  @param isAllowCc          是否採用 CC 授權
 *  @param commentrightType   留言權限
 *  @param password           相簿密碼(當 permission==PIXAlbumSetPermissionTypePassword 時為必要參數)
 *  @param passwordHint       相簿密碼提示(當 permission==PIXAlbumSetPermissionTypePassword 時為必要參數)
 *  @param friendGroupIds     好友群組ID，array 裡的值為 NSString instance(當 permission==PIXAlbumSetPermissionTypeGroup 時為必要參數)
 *  @param parentId           如果這個 parent_id 被指定, 則此相簿會放置在這個相簿資料夾底下(只能放在資料夾底下)
 *  @param completion         succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)createAlbumSetWithTitle:(NSString *)setTitle description:(NSString *)setDescription permission:(PIXAlbumSetPermissionType)permission isAllowCC:(BOOL)isAllowCc commentRightType:(PIXAlbumSetCommentRightType)commentRightType password:(NSString *)password passwordHint:(NSString *)passwordHint friendGroupIDs:(NSArray *)friendGroupIds parentID:(NSString *)parentId completion:(PIXHandlerCompletion)completion;
/**
 *  修改相簿 http://developer.pixnet.pro/#!/doc/pixnetApi/albumSetsUpdate
 *
 *  @param setId              欲修改的該相簿 ID
 *  @param setTitle           相簿標題，必要參數
 *  @param setDescription     相簿描述，必要參數
 *  @param permission         相簿閱讀權限
 *  @param categoryId         相簿分類
 *  @param isLockRight        是否鎖右鍵
 *  @param isAllowCc          是否採用 CC 授權
 *  @param commentRightType   留言權限
 *  @param password           相簿密碼(當 permission==PIXAlbumSetPermissionTypePassword 時為必要參數)
 *  @param passwordHint       相簿密碼提示(當 permission==PIXAlbumSetPermissionTypePassword 時為必要參數)
 *  @param friendGroupIds     好友群組ID，array 裡的值為 NSString instance(當 permission==PIXAlbumSetPermissionTypeGroup 時為必要參數)
 *  @param allowCommercialUse 是否允許商業使用
 *  @param allowDerivation    是否允許創作衍生著作
 *  @param parentId           如果這個 parent_id 被指定, 則此相簿會放置在這個相簿資料夾底下(只能放在資料夾底下)
 *  @param completion         succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)updateAlbumSetWithSetID:(NSString *)setId setTitle:(NSString *)setTitle setDescription:(NSString *)setDescription permission:(PIXAlbumSetPermissionType)permission categoryID:(NSString *)categoryId isLockRight:(BOOL)isLockRight isAllowCC:(BOOL)isAllowCc commentRightType:(PIXAlbumSetCommentRightType)commentRightType password:(NSString *)password passwordHint:(NSString *)passwordHint friendGroupIDs:(NSArray *)friendGroupIds allowCommercialUse:(BOOL)allowCommercialUse allowDerivation:(BOOL)allowDerivation parentID:(NSString *)parentId completion:(PIXHandlerCompletion)completion;
/**
 *  刪除單一相簿 http://developer.pixnet.pro/#!/doc/pixnetApi/albumSetsDelete
 *
 *  @param setId      欲刪除的相簿的 ID
 *  @param completion succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)deleteAlbumSetWithSetID:(NSString *)setId completion:(PIXHandlerCompletion)completion;
/**
 *  列出相本裡有些什麼東西 http://developer.pixnet.pro/#!/doc/pixnetApi/albumElements
 *
 *  @param userName    相本擁有者, 必要參數
 *  @param setId       指定要回傳的 set 的資訊, 必要參數
 *  @param elementType 指定要回傳的類別
 *  @param page        頁數
 *  @param password    相簿密碼，當使用者相簿設定為密碼相簿時使用
 *  @param completion  succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)getAlbumSetElementsWithUserName:(NSString *)userName setID:(NSString *)setId elementType:(PIXAlbumElementType)elementType page:(NSUInteger)page password:(NSString *)password completion:(PIXHandlerCompletion)completion;
/**
 *  列出相本(或照片)的留言 http://developer.pixnet.pro/#!/doc/pixnetApi/albumSetComments
 *
 *  @param userName   相本擁有者, 必要參數
 *  @param elementId  指定要回傳的留言所在的相簿 setID 與 elementID 只要指定其中一個即可, 未用到的參數請給0
 *  @param setId      指定要回傳的留言所在的相簿 setID 與 elementID 只要指定其中一個即可, 未用到的參數請給0
 *  @param password   如果指定使用者的相簿被密碼保護，則需要指定這個參數以通過授權
 *  @param page       頁數
 *  @param completion succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)getAlbumSetCommentsWithUserName:(NSString *)userName setID:(NSString *)setId password:(NSString *)password page:(NSUInteger)page completion:(PIXHandlerCompletion)completion;
/**
 *  新增一則相簿上的留言 http://developer.pixnet.pro/#!/doc/pixnetApi/albumSetCommentsCreate
 *
 *  @param setId      相簿 ID
 *  @param body       留言內容
 *  @param password   如果被留言的相本被密碼保護，則需要指定這個參數以通過授權
 *  @param completion succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)createAlbumSetCommentWithSetID:(NSString *)setId body:(NSString *)body password:(NSString *)password completion:(PIXHandlerCompletion)completion;
/**
 *  新增一則相片上的留言 http://developer.pixnet.pro/#!/doc/pixnetApi/albumCommentsCreate
 *
 *  @param elementID  相片 ID
 *  @param body       留言內容
 *  @param password   如果被留言的相本被密碼保護，則需要指定這個參數以通過授權
 *  @param completion succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)createElementCommentWithElementID:(NSString *)elementID body:(NSString *)body password:(NSString *)password completion:(PIXHandlerCompletion)completion;
/**
 *  附近的相本 http://developer.pixnet.pro/#!/doc/pixnetApi/albumSetsNearby
 *
 *  @param userName    相本擁有者, 必要參數
 *  @param location    經緯度坐標, 必要參數
 *  @param distanceMin 回傳相簿所在地和指定的經緯度距離之最小值，單位為公尺。預設為 0 公尺，上限為 50000 公尺
 *  @param distanceMax 回傳相簿所在地和指定的經緯度距離之最大值，單位為公尺。預設為 0 公尺，上限為 50000 公尺
 *  @param page        頁數
 *  @param completion  succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)getAlbumSetsNearbyWithUserName:(NSString *)userName location:(CLLocationCoordinate2D)location distanceMin:(NSUInteger)distanceMin distanceMax:(NSUInteger)distanceMax page:(NSUInteger)page completion:(PIXHandlerCompletion)completion;

#pragma mark Folders(PIXNET VIP 才會有 folder)
/**
 *  列出某個使用者所有的資料夾 http://developer.pixnet.pro/#!/doc/pixnetApi/albumFolders
 *
 *  @param userName   相本擁有者, 必要參數
 *  @param trimUser   是否每本相簿都要回傳使用者資訊，若設定為 YES 則不回傳
 *  @param page       頁數
 *  @param completion succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)getAlbumFoldersWithUserName:(NSString *)userName trimUser:(BOOL)trimUser page:(NSUInteger)page completion:(PIXHandlerCompletion)completion;
/**
 *  列出某個使用者單一資料夾裡有些什麼東西 http://developer.pixnet.pro/#!/doc/pixnetApi/albumFoldersShow
 *
 *  @param userName   相本擁有者, 必要參數
 *  @param folderId   指定要回傳的 folder 資訊, 必要參數
 *  @param page       頁數
 *  @param completion succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)getAlbumFolderWithUserName:(NSString *)userName folderID:(NSString *)folderId page:(NSUInteger)page completion:(PIXHandlerCompletion)completion;
/**
 *  修改資料夾裡的相簿排序 http://developer.pixnet.pro/#!/doc/pixnetApi/albumSetsPosition
 *
 *  @param parentId   屬於哪一個相簿資料夾
 *  @param ids        相簿id, array 裡的值為 NSString, id 的順序即為相簿的新順序
 *  @param completion succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)sortAlbumSetsWithParentID:(NSString *)parentId IDs:(NSArray *)ids completion:(PIXHandlerCompletion)completion;
/**
 *  新增資料夾 http://developer.pixnet.pro/#!/doc/pixnetApi/albumFoldersCreate
 *
 *  @param folderTitle       資料夾標題
 *  @param folderDescription 資料夾描述
 *  @param completion        succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)createAlbumFolderWithTitle:(NSString *)folderTitle description:(NSString *)folderDescription completion:(PIXHandlerCompletion)completion;
/**
 *  修改資料夾 http://developer.pixnet.pro/#!/doc/pixnetApi/albumFoldersUpdate
 *
 *  @param folderId          資料夾 ID
 *  @param folderTitle       資料夾標題
 *  @param folderDescription 資料夾描述
 *  @param completion        succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)updateAlbumFolderWithFolderID:(NSString *)folderId title:(NSString *)folderTitle description:(NSString *)folderDescription completion:(PIXHandlerCompletion)completion;
/**
 *  刪除資料夾 http://developer.pixnet.pro/#!/doc/pixnetApi/albumFoldersDelete
 *
 *  @param folderId  資料夾 ID
 *  @param comletion succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)deleteAlbumFolderWithFolderID:(NSString *)folderId completion:(PIXHandlerCompletion)completion;

#pragma mark Element
/**
 *  附近的相片 http://developer.pixnet.pro/#!/doc/pixnetApi/albumElementsNearby
 *
 *  @param userName    相本擁有者, 必要參數
 *  @param location    經緯度坐標, 必要參數
 *  @param distanceMin 回傳相簿所在地和指定的經緯度距離之最小值，單位為公尺。預設為 0 公尺，上限為 50000 公尺
 *  @param distanceMax 回傳相簿所在地和指定的經緯度距離之最大值，單位為公尺。預設為 0 公尺，上限為 50000 公尺
 *  @param page        頁數
 *  @param withDetail  是否傳回詳細資訊，指定為 YES 時將傳回相片／影音完整資訊及所屬相簿資訊。
 *  @param type        指定要回傳的類別。
 *  @param completion  succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)getElementsNearbyWithUserName:(NSString *)userName location:(CLLocationCoordinate2D)location distanceMin:(NSUInteger)distanceMin distanceMax:(NSUInteger)distanceMax page:(NSUInteger)page withDetail:(BOOL)withDetail type:(PIXAlbumElementType)type completion:(PIXHandlerCompletion)completion;
/**
 *  取得單一照片 http://developer.pixnet.pro/#!/doc/pixnetApi/albumElementsId
 *
 *  @param userName   相本擁有者，必要參數
 *  @param elementId  照片 ID，必要參數
 *  @param completion succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)getElementWithUserName:(NSString *)userName elementID:(NSString *)elementId completion:(PIXHandlerCompletion)completion;

/**
 *  新增相簿圖片影片 http://developer.pixnet.pro/#!/doc/pixnetApi/albumElementsCreate
 *
 *  @param elementData             必要參數，圖片的 NSData instance，如果有使用 base64 加密，在 dataIsBase64Encoded 需為 YES
 *  @param setId                   必要參數，上傳進哪本相簿的相簿 ID
 *  @param elementTitle            照片(或影片)標題
 *  @param elementDescription      照片(或影片)描述
 *  @param tags                    由 NSString instance 組成的 array
 *  @param location                照片(或影片)的經緯度，如不需要此參數，可使用 kCLLocationCoordinate2DInvalid
 */
-(void)addElementWithElementData:(NSData *)elementData setID:(NSString *)setId elementTitle:(NSString *)elementTitle elementDescription:(NSString *)elementDescription tags:(NSArray *)tags location:(CLLocationCoordinate2D)location completion:(PIXHandlerCompletion)completion;

/**
 *  修改圖片(或影片)裡的參數 http://developer.pixnet.pro/#!/doc/pixnetApi/albumElementsUpdate
 *
 *  @param elementId          圖片(或影片)的 ID，必要參數
 *  @param elementTitle       圖片(或影片)標題
 *  @param elementDescription 圖片(或影片)描述
 *  @param setId              圖片(或影片)所屬的相簿 ID
 *  @param videoThumbType     影片截圖類型，如不設定請給 PIXVideoThumbTypeNone
 *  @param tags               由 NSString instance 組成的 array
 *  @param location           照片(或影片)的經緯度，如不需要此參數，可使用 kCLLocationCoordinate2DInvalid
 *  @param completion         succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)updateElementWithElementID:(NSString *)elementId elementTitle:(NSString *)elementTitle elementDescription:(NSString *)elementDescription setID:(NSString *)setId videoThumbType:(PIXVideoThumbType)videoThumbType tags:(NSArray *)tags location:(CLLocationCoordinate2D)location completion:(PIXHandlerCompletion)completion;
/**
 *  刪除單張圖片(或影片) http://developer.pixnet.pro/#!/doc/pixnetApi/albumElementsDelete
 *
 *  @param elementId  圖片(或影片)的 ID, 必要參數
 *  @param completion succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)deleteElementWithElementID:(NSString *)elementId completion:(PIXHandlerCompletion)completion;
/**
 *  修改相簿裡圖片影片排序 http://developer.pixnet.pro/#!/doc/pixnetApi/albumElementsPosition
 *
 *  @param setId      相簿 ID，必要參數
 *  @param ids        圖片 ID, array 裡的值為 NSString, id 的順序即為圖片的新順序，必要參數
 *  @param completion succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)sortElementsWithSetID:(NSString *)setId elementIDs:(NSArray *)ids completion:(PIXHandlerCompletion)completion;
/**
 *  取得相片裡的留言 http://developer.pixnet.pro/#!/doc/pixnetApi/albumComments
 *
 *  @param userName   相片擁有者名稱，必要參數
 *  @param elementId  相片 ID，必要參數
 *  @param password   相片所屬相簿如果有密碼保護，就代入這個參數
 *  @param page       頁數
 *  @param completion succeed=YES 時 result 可以用(而 errorMessage 就會是 nil)，succeed=NO 時 result 會是 nil，而錯誤原因會在 errorMessage 裡
 */
-(void)getElementCommentsWithUserName:(NSString *)userName elementID:(NSString *)elementId password:(NSString *)password page:(NSUInteger)page completion:(PIXHandlerCompletion)completion;
#pragma mark 留言
/**
 *  取得單一則留言 http://developer.pixnet.pro/#!/doc/pixnetApi/albumCommentsId
 *
 *  @param userName   相片或相簿的擁有者名稱，必要參數
 *  @param commentId  該則留言ID，必要參數
 *  @param completion succeed=YES 時 result 可以用(而 errorMessage 就會是 nil)，succeed=NO 時 result 會是 nil，而錯誤原因會在 errorMessage 裡
 */
-(void)getCommentWithUserName:(NSString *)userName commentID:(NSString *)commentId completion:(PIXHandlerCompletion)completion;
/**
 *  將某則留言標記為廣告留言 http://developer.pixnet.pro/#!/doc/pixnetApi/albumCommentsMarkSpam
 *
 *  @param commentId  留言ID, 必要參數
 *  @param completion succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)markCommentAsSpamWithCommentID:(NSString *)commentId completion:(PIXHandlerCompletion)completion;
/**
 *  將某則留言標記為非廣告留言 http://developer.pixnet.pro/#!/doc/pixnetApi/albumCommentsMarkHam
 *
 *  @param commentId  留言ID, 必要參數
 *  @param completion succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)markCommentAsHamWithCommentID:(NSString *)commentId completion:(PIXHandlerCompletion)completion;
/**
 *  刪除某則留言 http://developer.pixnet.pro/#!/doc/pixnetApi/albumCommentsDelete
 *
 *  @param commentId  留言ID, 必要參數
 *  @param completion succeed=YES 時 result 可以用(errorMessage為 nil)，succeed=NO 時 result會是 nil，錯誤原因會在 errorMessage 裡
 */
-(void)deleteCommentWithCommentID:(NSString *)commentId completion:(PIXHandlerCompletion)completion;
@end
